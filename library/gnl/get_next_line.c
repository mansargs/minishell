/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:18:34 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/21 18:15:04 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *line)
{
	char	*buf;
	int		bytes;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (clear(&line), NULL);
	while (1)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
			return (clear(&line), free(buf), NULL);
		if (bytes == 0)
			break ;
		buf[bytes] = '\0';
		line = ft_strjoin(line, buf);
		if (ft_strchr(line, '\n'))
			break ;
	}
	return (free(buf), line);
}

static char	*cut_line(char *line)
{
	char	*newline_pos;
	char	*cut;

	newline_pos = ft_strchr(line, '\n');
	if (newline_pos)
		cut = ft_substr(line, 0, newline_pos - line + 1);
	else
		cut = ft_substr(line, 0, ft_strlen(line));
	if (!cut)
		return (NULL);
	return (cut);
}

static char	*cut_static(char *line)
{
	char	*temp;
	char	*newl;
	int		len;

	newl = ft_strchr(line, '\n');
	len = newl - line + 1;
	if (newl)
	{
		temp = ft_substr(line, len, ft_strlen(line) - len);
		clear(&line);
		line = temp;
	}
	else
	{
		clear(&line);
		line = (char *)malloc(sizeof(char) * 1);
		if (!line)
			return (NULL);
		line[0] = '\0';
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line = NULL;
	char		*cut;

	cut = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	line = read_line(fd, line);
	if (!line || (line && line[0] == '\0'))
		return (clear(&line), NULL);
	cut = cut_line(line);
	if (!cut)
		return (clear (&line), NULL);
	line = cut_static(line);
	return (cut);
}
