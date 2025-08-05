/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 06:29:12 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/04 06:32:57 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

bool	find_directory_and_word(const char *line, char **dir, char **word)
{
	char	*last_backslash;

	last_backslash = ft_strrchr(line, '/');
	if (!last_backslash)
	{
		*dir = ft_strdup(".");
		*word = ft_strdup(line);
	}
	else
	{
		*dir = ft_substr(line, 0, last_backslash - line);
		*word = ft_substr(line, last_backslash - line + 1,
				ft_strlen(last_backslash + 1));
	}
	if (!*dir || !*word)
	{
		free(*dir);
		free(*word);
		return (false);
	}
	return (true);
}

static bool	match_loop(const char **item, const char **cpy_pattern,
			const char **star, const char **match)
{
	while (**item)
	{
		if (**item == **cpy_pattern)
		{
			(*item)++;
			(*cpy_pattern)++;
		}
		else if (**cpy_pattern == '*')
		{
			*star = (*cpy_pattern)++;
			*match = *item;
		}
		else if (*star)
		{
			*cpy_pattern = *star + 1;
			(*match)++;
			*item = *match;
		}
		else
			return (false);
	}
	return (true);
}

bool	is_match(const char *item_name, const char *pattern)
{
	const char	*item;
	const char	*cpy_pattern;
	const char	*star;
	const char	*match;

	item = item_name;
	cpy_pattern = pattern;
	star = NULL;
	match = NULL;
	if (!match_loop(&item, &cpy_pattern, &star, &match))
		return (false);
	while (*cpy_pattern == '*')
		++cpy_pattern;
	return (*cpy_pattern == '\0');
}

int	count_lines(char	**lines)
{
	int	i;

	if (!lines)
		return (0);
	i = 0;
	while (lines[i])
		++i;
	return (i);
}

bool	copy_and_duplicate_old_args(char **new_arg_list, char **old_args)
{
	int	i;

	i = 0;
	while (old_args[i])
	{
		new_arg_list[i] = ft_strdup(old_args[i]);
		if (!new_arg_list[i])
		{
			while (--i >= 0)
				free(new_arg_list[i]);
			free(new_arg_list);
			return (false);
		}
		++i;
	}
	return (true);
}
