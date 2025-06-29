/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paren.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:34:03 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/29 13:03:42 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	close_paren_without_open(t_token *token)
{
	t_token	*tmp;
	int		paren;

	tmp = token;
	paren = 0;
	while (tmp)
	{
		if (tmp->token_operator_type == OPERATOR_PAREN_OPEN)
			paren++;
		else if (tmp->token_operator_type == OPERATOR_PAREN_CLOSE)
			paren--;
		if (paren < 0)
			return (printf("%s `)'\n", SYN_ERR), true);
		tmp = tmp->prev_token;
	}
	return (false);
}

bool	empty_parens(t_token *token)
{
	if (token->next_token && token->token_operator_type == OPERATOR_PAREN_OPEN
			&& token->token_operator_type == OPERATOR_PAREN_CLOSE)
		return (printf("%s `)'\n", SYN_ERR), true);
	return (false);
}

bool	operator_after_word(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->token_type == TOKEN_WORD)
		{
			if (tmp->next_token
				&& tmp->next_token->token_operator_type == OPERATOR_PAREN_CLOSE)
				return (printf("%s `%s'\n", SYN_ERR,
						tmp->next_token->token_data), true);
		}
		tmp = tmp->next_token;
	}
	return (false);
}

bool	invalid_open_parenthesis(const t_token *token)
{
	if (token->token_operator_type == OPERATOR_PAREN_OPEN
		&& token->prev_token && (token->prev_token->token_type == TOKEN_REDIRECT || token->prev_token->token_type == TOKEN_WORD))
				return (printf("%s `('\n", SYN_ERR), true);
	if (token->token_operator_type == OPERATOR_PAREN_OPEN && token->next_token
		&& (token->next_token->token_type == TOKEN_OPERATOR && token->next_token->token_operator_type != OPERATOR_PAREN_OPEN))
		return (printf("%s `%s'\n", SYN_ERR, token->next_token->token_data), true);
	return (false);
}
