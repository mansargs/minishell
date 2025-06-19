/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defective_operator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:51:12 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/19 15:00:28 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

static char	*find_last_word(const char *line)
{
	int		i;
	int		end;
	int		start;
	char	*last;

	if (!line || !*line)
		return (NULL);
	i = ft_strlen(line) - 1;
	while (i >= 0 && is_space(line[i]))
		--i;
	if (i < 0)
		return (NULL);
	end = i;
	while (i >= 0 && !is_space(line[i]))
		--i;
	start = i + 1;
	last = ft_substr(line, start, end - start + 1);
	return (last);
}

static bool	should_I_wait(const char *last_word)
{
	int	len;

	len = ft_strlen(last_word);
	if ((len >= 2 && (!ft_strncmp(last_word + len - 2, "||", 2)
		|| !ft_strncmp(last_word + len - 2, "&&", 2)))
		|| (len >= 1 && !ft_strncmp(last_word + len - 1, "|", 1)))
		return (true);
	return (false);
}

bool	wait_for_input_if_need(char **line)
{
	char	*last_word;
	char	*extra_line;
	char	*temp;

	while (1)
	{
		last_word = find_last_word(*line);
		if (!last_word)
			return (false);
		if (!should_I_wait(last_word))
			break ;
		free(last_word);
		extra_line = readline(" > ");
		if (!extra_line)
			return (false);
		temp = *line;
		*line = ft_strjoin(*line, extra_line);
		free(extra_line);
		free(temp);
		if (!*line)
			return (false);
	}
	return (free(last_word), true);
}
