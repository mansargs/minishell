/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 00:08:56 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/19 15:56:08 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"

bool	is_space(char tok)
{
	return (tok == ' ' || (tok >= '\t' && tok <= '\r'));
}

bool	is_special_char(char tok)
{
	return (tok == '|' || tok == '&' || tok == '<' || tok == '>'
		|| tok == '(' || tok == ')' || tok == '\\' || tok == ';');
}

bool	is_redirect(char tok)
{
	return (tok == '<' || tok == '>');
}

bool	is_special_operator(char tok)
{
	return (tok == '&' || tok == '(' || tok == ')'
		|| tok == '|' || tok == ';');
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next_token;
		free(tmp->token_data);
		free(tmp);
	}
}
