/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:28:36 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/20 01:28:37 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"

static int	add_quoted_token(char *line, int start,
	t_token **head, int j)
{
	char	*substr;
	t_token	*new_token;

	substr = ft_substr(line, start, j - start);
	if (!substr)
		return (-1);
	new_token = create_token(substr, TOKEN_CLASS_WORD, TOKEN_WORD);
	free(substr);
	if (!new_token)
		return (-1);
	add_token(head, new_token);
	return (0);
}

int	handle_quoted_token(char *line, int i, t_token **head)
{
	int		start;
	int		j;
	char	quote;

	start = i;
	j = i;
	while (line[j])
	{
		if (line[j] == '\'' || line[j] == '"')
		{
			quote = line[j++];
			while (line[j] && line[j] != quote)
				j++;
			if (line[j] == quote)
				j++;
		}
		else if (!is_space(line[j]) && !is_special_char(line[j]))
			j++;
		else
			break ;
	}
	if (add_quoted_token(line, start, head, j) < 0)
		return (-1);
	return (j - i);
}
