/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strict_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:55:20 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/01 20:52:58 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	invalid_redirect(const t_token *token, const int strict_flag)
{
	if (strict_flag)
	{
		if (token->next_token && token->next_token->token_type
			== TOKEN_REDIRECT)
			return (printf("%s `%s'\n", SYN_ERR,
					token->next_token->token_data), true);
		if (token->next_token && (token->next_token->token_type
				== TOKEN_OPERATOR || token->next_token->token_paren_type
				== PAREN_OPEN))
			return (printf("%s `%s'\n", SYN_ERR,
					token->next_token->token_data), true);
	}
	else
	{
		if (!token->next_token)
			return (printf("%s `newline'\n", SYN_ERR), true);
		if (token->prev_token && token->prev_token->token_paren_type
			== PAREN_CLOSE
			&& token->next_token->next_token
			&& token->next_token->next_token->token_type == TOKEN_WORD)
			return (printf("%s `%s'\n", SYN_ERR,
					token->next_token->next_token->token_data), true);
	}
	return (false);
}

bool	invalid_operator(const t_token *token, const int strict_flag)
{
	if (strict_flag)
	{
		if (!token->prev_token && token->token_type == TOKEN_OPERATOR)
			return (printf("%s `%s'\n", SYN_ERR, token->token_data), true);
		if (token->next_token
			&& token->next_token->token_type == TOKEN_OPERATOR)
			return (printf("%s `%s'\n", SYN_ERR, token->next_token->token_data),
				true);
		if (token->next_token && token->next_token->token_type
			== TOKEN_OPERATOR)
			return (printf("%s `%s'\n", SYN_ERR,
					token->next_token->token_data), true);
	}
	else
	{
		if (token->next_token && token->next_token->token_paren_type
			== PAREN_CLOSE)
			return (printf("%s `%s'\n", SYN_ERR, token->next_token->token_data),
				true);
	}
	return (false);
}

bool	check_heredoc_case(t_shell *shell, t_token *token)
{
	t_token	*tmp;
	char	*parsed;
	int		open_flag;

	open_flag = 0;
	if (token->token_redirect_type == REDIRECT_HEREDOC
		&& token->next_token
		&& token->next_token->token_type == TOKEN_WORD)
	{
		tmp = token->next_token;
		parsed = open_quotes_heredoc(shell, tmp->token_data,
				&open_flag);
		if (!parsed)
			return (true);
		free(tmp->token_data);
		tmp->token_data = parsed;
	}
	return (false);
}

bool	strict_syntax_errors(t_shell *shell)
{
	t_token	*temp;

	temp = shell->tokens;
	while (temp)
	{
		if (temp->token_type == TOKEN_REDIRECT)
			if (invalid_redirect(temp, STRICT))
				return (true);
		check_heredoc_case(shell, temp);
		if (temp->token_type == TOKEN_OPERATOR)
			if (invalid_operator(temp, STRICT))
				return (true);
		temp = temp->next_token;
	}
	return (false);
}
