/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:38:09 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/29 16:05:10 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static bool	invalid_word(const t_token *token)
{
	if (token->next_token && token->next_token->token_operator_type == OPERATOR_PAREN_OPEN)
		return (printf("%s `('\n", SYN_ERR), true);
	return (false);
}

static bool	last_is_redirection(const t_token *token)
{
	if (!token->next_token)
		return (printf("%s `newline'\n", SYN_ERR), true);
}

static bool	is_there_open_parenthesis(const t_token *token)
{
	t_token	*temp;

	temp = token;
	while(temp && temp->token_redirect_type != REDIRECT_HEREDOC)
	{
		if (temp->token_operator_type == OPERATOR_PAREN_OPEN)
			return (true);
		temp = temp->prev_token;
	}
	return (false);
}

static bool	invalid_redirect(const t_token *token)
{
	if (token->next_token && token->next_token->token_type == TOKEN_REDIRECT)
		printf("%s `%s'\n", SYN_ERR, token->next_token->token_data);
	if (token->next_token->token_type == TOKEN_OPERATOR)
	{
		if (token->next_token->token_operator_type == OPERATOR_PAREN_CLOSE)
			if (!is_there_open_parenthesis(token->prev_token))
				printf("%s `%s'\n", SYN_ERR, token->next_token->token_data);
		else
			printf("%s `%s'\n", SYN_ERR, token->next_token->token_data);
	}
}

static bool	invalid_operator(const t_token *token)
{
	if (!token->prev_token && token->token_operator_type != OPERATOR_PAREN_OPEN)
		printf("%s `%s'\n", SYN_ERR, token->token_data);
	if (token->next_token && token->next_token->token_type == TOKEN_OPERATOR)
		printf("%s `%s'\n", SYN_ERR, token->next_token->token_data);
}

bool	syntax_analysis(t_token *token)
{
	if (last_is_redirection(token))
		return (true);
	if (invalid_open_parenthesis	(token))
		return (true);
	if (empty_parens(token))
		return (true);
	if (operator_after_open_paren(token))
		return (true);
	if (operator_before_close_paren(token))
		return (true);
	if (close_paren_without_open(token))
		return (true);
	return (false);
}
