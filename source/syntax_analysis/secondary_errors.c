/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 03:03:48 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/30 16:04:00 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static bool	invalid_word(const t_token *token)
{
	if (token->next_token && token->next_token->token_operator_type == OPERATOR_PAREN_OPEN)
		return (printf("%s `('\n", SYN_ERR), true);
	return (false);
}

static bool	redirection_secondary_errors(const t_token *token)
{
	if (!token->next_token)
		return (printf("%s `newline'\n", SYN_ERR), true);
	if (invalid_redirect(token))
		return (true);
	return (false);
}

static int	count_parenthesis(t_token *token)
{
	int		count;
	t_token	*temp;

	count = 0;
	temp = token;
	while (temp)
	{
		if (temp->token_operator_type == OPERATOR_PAREN_OPEN)
			++count;
		else if (temp->token_operator_type == OPERATOR_PAREN_CLOSE)
			--count;
		temp = temp->prev_token;
	}
	return (count);
}

bool	secondary_syntax_errors(const t_token *token)
{
	if (token->token_type == TOKEN_REDIRECT && redirection_secondary_errors(token))
			return (true);
	if (token->token_type == TOKEN_WORD && invalid_word(token))
			return (true);
	if (token->token_operator_type == OPERATOR_PAREN_CLOSE && count_parenthesis((t_token *) token) < 0)
			return (printf("%s `)'\n", SYN_ERR), true);
	if (token->token_type == TOKEN_OPERATOR && invalid_operator(token, NOT_STRICT))
		return (true);
	return (false);
}
