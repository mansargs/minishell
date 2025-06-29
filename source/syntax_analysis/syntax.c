/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:38:09 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/30 03:05:42 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"





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

bool	invalid_redirect(const t_token *token)
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

bool	invalid_operator(const t_token *token)
{
	if (!token->prev_token && token->token_operator_type != OPERATOR_PAREN_OPEN)
		printf("%s `%s'\n", SYN_ERR, token->token_data);
	if (token->next_token && token->next_token->token_type == TOKEN_OPERATOR)
		printf("%s `%s'\n", SYN_ERR, token->next_token->token_data);
}

bool	secondary_syntax_errors(t_token *token)
{
	if (token == TOKEN_REDIRECT)
		if (last_is_redirection(token))
			return (true);
	if (token == TOKEN_WORD)
		if (invalid_word(token))
			return (true);
	if ()
	return (false);
}


bool	syntax_and_heredoc(t_token *tokens, char **line)
{
	t_token			*temp;
	unsigned int	i;

	if (strict_syntax_errors(tokens))
		return (free_tokens(tokens), false);
	temp = tokens;
	while (temp)
	{
		++i;
		if (temp->token_redirect_type == REDIRECT_HEREDOC)
		{
			if (!temp->file_name)
				temp->file_name = open_heredoc(temp, &i);
			if (!temp->file_name)
				return (false);
		}
		else if (secondary_(temp))
			return (free_tokens(tokens), false);
		temp = temp->next_token;
	}
	if (should_I_wait(tokens->prev_token))
	{
		if (!wait_for_input(temp, line))
			return (false);
		return (syntax_and_heredoc(tokens, line));
	}
	return (true);
}
