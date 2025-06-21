/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:06:39 by mansargs          #+#    #+#             */
/*   Updated: 2025/01/26 14:39:09 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	int		inside_word;
	size_t	len;

	len = 0;
	while (*s)
	{
		inside_word = 0;
		while (*s && *s == c)
			++s;
		while (*s && *s != c)
		{
			if (!inside_word)
			{
				++len;
				inside_word = 1;
			}
			++s;
		}
	}
	return (len);
}

static int	safe_malloc(char **split, int idx, size_t size)
{
	int	i;

	i = 0;
	split[idx] = (char *)malloc(size * sizeof(char));
	if (split[idx] == NULL)
	{
		while (i < idx)
		{
			free(split[i]);
			++i;
		}
		free(split);
		return (0);
	}
	return (1);
}

static int	fill(char **split, char const *s, char c)
{
	size_t	len;
	int		i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s && *s == c)
			++s;
		while (*s && *s != c)
		{
			++len;
			++s;
		}
		if (len)
		{
			if (!safe_malloc(split, i, len + 1))
				return (0);
			ft_strlcpy(split[i], s - len, len + 1);
		}
		++i;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	len;
	char	**split;

	len = count_words(s, c);
	split = (char **)malloc((len + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	split[len] = NULL;
	if (!fill(split, s, c))
		return (NULL);
	return (split);
}
