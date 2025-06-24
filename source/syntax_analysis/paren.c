/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paren.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:34:03 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/24 16:10:52 by alisharu         ###   ########.fr       */
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
		{
			printf("minishell: syntax error near unexpected token `)'\n");
			return (true);
		}
		tmp = tmp->next_token;
	}
	return (false);
}

bool	empty_parens(t_token *head)
{
	t_token	*tmp;
	t_token	*check;

	tmp = head;
	while (tmp)
	{
		if (tmp->token_operator_type == OPERATOR_PAREN_OPEN)
		{
			check = tmp->next_token;
			while (check)
			{
				if (check->token_operator_type == OPERATOR_PAREN_CLOSE)
				{
					if (check == tmp->next_token)
						return (printf("minishell: syntax error near unexpected token `%s'\n", check->token_data), true);
					break ;
				}
				else if (check->token_type == TOKEN_WORD)
					break ;
				check = check->next_token;
			}
		}
		tmp = tmp->next_token;
	}
	return (false);
}
