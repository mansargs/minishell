/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strict_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:55:20 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/02 14:53:06 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	invalid_word(const t_token *token)// es em avelacrel
{
	if (token->token_type == TOKEN_WORD && token->next_token
		&& token->next_token->token_operator_type == OPERATOR_PAREN_OPEN)
		return (printf("%s `('\n", SYN_ERR), true);
	return (false);
}

bool	invalid_redirect(const t_token *token, const int strict_flag)
{
	if (strict_flag)
	{
		if (token->next_token && token->next_token->token_type
			== TOKEN_REDIRECT)
			return (printf("%s `%s'\n", SYN_ERR,
					token->next_token->token_data), true);// >> >
		if (token->next_token && token->next_token->token_type
			== TOKEN_OPERATOR && token->next_token->token_operator_type
			!= OPERATOR_PAREN_CLOSE)// >> && 
			return (printf("%s `%s'\n", SYN_ERR,
					token->next_token->token_data), true);
	}
	else
	{
		if (!token->next_token)
			return (printf("%s `newline'\n", SYN_ERR), true);// ls <<
	}
	if (token->next_token->token_type != TOKEN_WORD)// >> (n
		return (printf("%s `%s'\n", SYN_ERR,
				token->next_token->token_data), true);
	return (false);
}

bool	invalid_operator(const t_token *token, const int strict_flag)
{
	if (strict_flag)
	{
		if (token->next_token && token->next_token->token_type == TOKEN_OPERATOR
			&& token->next_token->token_operator_type != OPERATOR_PAREN_OPEN)
			return (printf("%s `%s'\n", SYN_ERR,
					token->next_token->token_data), true);
	}
	else
	{
		if (token->token_type == TOKEN_OPERATOR
			&& token->token_operator_type == OPERATOR_PAREN_CLOSE
			&& token->next_token
			&& token->next_token->token_type == TOKEN_OPERATOR//
			&& token->next_token->token_operator_type == OPERATOR_PAREN_OPEN)
			return (printf("%s `%s'\n", SYN_ERR, token->next_token->token_data),
				true);
		if (!token->prev_token && token->token_type
			== TOKEN_OPERATOR && token->token_operator_type
			!= OPERATOR_PAREN_OPEN)
			return (printf("%s `%s'\n", SYN_ERR, token->token_data), true);
	}
	return (false);
}

bool	strict_syntax_errors(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		if (temp->token_type == TOKEN_REDIRECT)
			if (invalid_redirect(temp, STRICT))
				return (true);
		if (temp->token_type == TOKEN_OPERATOR) 
			if (invalid_operator(temp, STRICT))
				return (true);
		if (temp->token_type == TOKEN_WORD)
		{// es masy
			if (invalid_word(temp))
				return (true);
			if (handle_quoted(temp) == -1)
				return (true);
		}
		temp = temp->next_token;
	}
	return (false);
}
