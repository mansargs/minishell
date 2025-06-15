/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 00:08:56 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/15 17:16:11 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"

int	is_space(char tok)
{
	return (tok == ' ' || tok == '\t' || tok == '\n'
		|| tok == '\v' || tok == '\f' || tok == '\r');
}

int	is_special_char(char tok)
{
	return (tok == '|' || tok == '&' || tok == '<' || tok == '>'
		|| tok == '(' || tok == ')' || tok == '\\' || tok == '$');
}

int	is_redirect(char tok)
{
	return (tok == '<' || tok == '>');
}

int	is_special_operator(char tok)
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
