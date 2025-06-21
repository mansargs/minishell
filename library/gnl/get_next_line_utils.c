/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:18:52 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/21 18:13:08 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clear(char **line)
{
	if (*line && line)
		free (*line);
	*line = NULL;
}

char	*ft_gnl_strchr(const char *str, int c)
{
	unsigned char	search_char;

	if (!str)
		return (NULL);
	search_char = (unsigned char)c;
	if (search_char == '\0')
		return ((char *)str + ft_strlen(str));
	while (*str != '\0')
	{
		if (*str == search_char)
			return ((char *)str);
		++str;
	}
	return (NULL);
}

size_t	ft_gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		++i;
	return (i);
}

char	*ft_gnl_strjoin(char *line, const char *buf)
{
	char	*res;
	size_t	len1;
	size_t	len2;
	int		i;

	i = -1;
	if (!line && !buf)
		return (NULL);
	len1 = ft_strlen(line);
	len2 = ft_strlen(buf);
	res = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!res)
		return (clear(&line), NULL);
	while ((size_t)++i < len1)
			res[i] = line[i];
	i = -1;
	while ((size_t)++i < len2)
		res[len1 + i] = buf[i];
	res[len1 + len2] = '\0';
	clear(&line);
	return (res);
}

char	*ft_gnl_substr(const char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (NULL);
	if (len > s_len - start)
		len = s_len - start;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		++i;
	}
	str[i] = '\0';
	return (str);
}
