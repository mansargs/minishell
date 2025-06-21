/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 00:08:56 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/21 18:34:40 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

bool	is_space(char tok)
{
	return (tok == ' ' || (tok >= '\t' && tok <= '\r'));
}

bool	is_special_char(char tok)
{
	return (tok == '|' || tok == '&' || tok == '<' || tok == '>'
		|| tok == '(' || tok == ')');
}

bool	is_redirect(char tok)
{
	return (tok == '<' || tok == '>');
}

bool	is_special_operator(char tok)
{
	return (tok == '&' || tok == '(' || tok == ')'
		|| tok == '|');
}

int	skip_variable(const char *line, int i)
{
	i++;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	return (i);
}
