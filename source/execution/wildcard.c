/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:31:07 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/21 21:39:22 by mansargs         ###   ########.fr       */
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
		*word = ft_substr(line, last_backslash - line + 1, ft_strlen(last_backslash + 1));
	}
	if (!*dir || !*word)
	{
		free(*dir);
		free(*word);
		return (false);
	}
	return (true);
}

bool is_match(const char *item_name, const char *word)
{
	int	i;

	i = 0;
	if (!item_name || !word)
		return (false);
	while (item_name[i] && word[i])
	{
		
	}
}

bool	open_directory(const char *dir, const char *word)
{
	DIR				*dir_content;
	struct dirent	*item;

	dir_content = opendir(dir);
	if (!dir_content)
		return (false);
	while (1)
	{
		item = readdir(dir_content);
		if(!item)
			break ;
		if (is_match(item->d_name, word))
	}
}

bool	open_wildcards(char	***argv)
{
	int		i;
	char	*dir;
	char	*word;

	i = -1;
	while (*argv[++i])
	{
		if (!find_directory_and_word(*argv[i], &dir, &word))
			return (false);
		open_directory(dir, word);
	}
	return (true);
}
