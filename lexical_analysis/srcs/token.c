/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:01:31 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/19 18:07:18 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"

static bool	ft_isspace(char *c)
{
	return (*c == ' ' || *c == '\t' || *c == '\n');
}

static bool	is_operation(char *c)
{
	return (*c == '|' || *c == '&');
}

static bool	is_redirection(char *c)
{
	return (*c == '<' || *c == '>');
}

int	handle_quoted_token(char *line, int i, t_token **head)
{
	char	*str;
	int		j;
	int		index;
	t_token	*new_token;

	str = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!str)
		return (-1);
	index = 0;
	j = i;
	while (line[j])
	{
		if (line[j] == '\'' || line[j] == '"')
		{
			while (line[j] && line[j] != ' ')
				str[index++] = line[j++];
			j++;
		}
		else if (!ft_isspace(line + j)
			&& !is_operation(line + j)
			&& !is_redirection(line + j))
		{
			str[index++] = line[j++];
		}
		else
			break ;
	}
	str[index] = '\0';
	new_token = create_token(str, TOKEN_CLASS_WORD, TOKEN_WORD);
	free(str);
	if (!new_token)
		return (-1);
	add_token(head, new_token);
	return (j - i);
}
