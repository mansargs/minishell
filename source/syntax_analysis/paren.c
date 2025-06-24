/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paren.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:34:03 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/24 19:15:56 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	close_paren_without_open(t_token *head)
{
	t_token	*tmp;
	int		paren;

	tmp = head;
	paren = 0;
	while (tmp)
	{
		if (tmp->token_operator_type == OPERATOR_PAREN_OPEN)
			paren++;
		else if (tmp->token_operator_type == OPERATOR_PAREN_CLOSE)
			paren--;
		if (paren < 0)
			return (printf("%s `%s'\n", SYN_ERR, ")"), true);
		tmp = tmp->next_token;
	}
	return (false);
}

bool	empty_parens(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->token_operator_type == OPERATOR_PAREN_OPEN)
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

bool	operator_before_paren(t_token *head)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = head;
	prev = NULL;
	while (tmp)
	{
		if (tmp->token_operator_type == OPERATOR_PAREN_OPEN)
			if (prev && (prev->token_type == TOKEN_WORD
					|| prev->token_type == TOKEN_REDIRECT
					|| prev->token_operator_type == OPERATOR_PAREN_CLOSE))
				return (printf("%s `%s'\n", SYN_ERR, "("), true);
		prev = tmp;
		tmp = tmp->next_token;
	}
	return (false);
}
