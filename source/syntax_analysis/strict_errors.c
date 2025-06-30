/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strict_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:55:20 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/30 12:47:19 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static bool	is_there_open_parenthesis(const t_token *token)
{
	t_token	*temp;

	temp = token;
	while(temp)
	{
		if (temp->token_operator_type == OPERATOR_PAREN_OPEN)
			break ;
		temp = temp->prev_token;
	}
	if (!temp)
		return (false);
	if (temp && (temp->prev_token || temp->prev_token->token_operator_type == OPERATOR_PIPE))
		return (false);
	while(temp)
	{
		if (temp->token_redirect_type == REDIRECT_HEREDOC)
			return (true);
		temp = temp->prev_token;
	}
	return (false);
}

bool	invalid_redirect(const t_token *token)
{

	if (token->next_token && token->next_token->token_type == TOKEN_REDIRECT)
		printf("%s `%s'\n", SYN_ERR, token->next_token->token_data);
	if (token->next_token->token_type == TOKEN_OPERATOR)
		printf("%s `%s'\n", SYN_ERR, token->next_token->token_data);
}

bool	invalid_operator(const t_token *token)
{
	if (!token->prev_token && token->token_operator_type != OPERATOR_PAREN_OPEN)
		printf("%s `%s'\n", SYN_ERR, token->token_data);
	if (token->next_token && token->next_token->token_type == TOKEN_OPERATOR)
		printf("%s `%s'\n", SYN_ERR, token->next_token->token_data);
}


bool	strict_syntax_errors(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		if (temp->token_type == TOKEN_REDIRECT && !is_there_open_parenthesis(temp))
			if (invalid_redirect(temp))
				return (true);
		if (temp->token_type == TOKEN_OPERATOR && !is_there_open_parenthesis(temp))
			if (invalid_operator(temp))
				return (true);
		temp = temp->next_token;
	}
	return (false);
}
