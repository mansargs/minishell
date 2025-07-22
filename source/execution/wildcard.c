/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:31:07 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/23 02:23:58 by mansargs         ###   ########.fr       */
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

bool is_match(const char *item_name, const char *pattern)
{
	const char	*item;
	const char	*cpy_pattern;
	const char	*star;
	const char	*match;

	item = item_name;
	cpy_pattern = pattern;
	star = NULL;
	match = NULL;
	while (*item)
	{
		if (*item == *cpy_pattern)
		{
			++item;
			++cpy_pattern;
		}
		else if (*cpy_pattern == '*')
		{
			star = cpy_pattern++;
			match = item;
		}
		else if (star)
		{
			cpy_pattern = star + 1;
			match++;
			item = match;
		}
		else
			return (false);
	}
	while(*cpy_pattern == '*')
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

bool	collect_matched(char	***matched, const char	*newly_added)
{
	char	**new_arg_list;
	int		i;

	if (!*newly_added)
		return (true);
	new_arg_list = ft_calloc(count_lines(*matched) + 2, sizeof(char *));
	if (!new_arg_list)
		return (false);
	i = 0;
	if (*matched)
	{
		while((*matched)[i])
		{
			new_arg_list[i] = ft_strdup((*matched)[i]);
			if (!new_arg_list[i])
			{
				while (--i >= 0)
					free(new_arg_list[i]);
				free(new_arg_list);
				return (false);
			}
			++i;
		}
	}
	new_arg_list[i] = ft_strdup(newly_added);
	if (!new_arg_list[i])
		return (free_matrix(&new_arg_list), false);
	new_arg_list[++i] = NULL;
	free_matrix(matched);
	*matched = new_arg_list;
	return (true);
}

bool	open_directory(const char *dir, const char *word, char ***incoming_arg)
{
	DIR				*dir_content;
	struct dirent	*item;

	*incoming_arg = NULL;
	dir_content = opendir(dir);
	if (!dir_content)
		return (true);
	while (1)
	{
		item = readdir(dir_content);
		if(!item)
			break ;
		if (is_match(item->d_name, word))
			if (!collect_matched(incoming_arg, item->d_name))
				return (free_matrix(incoming_arg), closedir(dir_content), false);
	}
	closedir(dir_content);
	return (true);
}

bool	integration(char ***argv, char **replace, int replace_index)
{
	char	**new_argv;
	int		i;
	int		j;

	if (!replace)
		return (true);
	new_argv = ft_calloc(count_lines(*argv) + count_lines(replace) + 1, sizeof (char *));
	if (!new_argv)
		return (false);

	i = -1;
	while (++i < replace_index)
	{
		new_argv[i] = ft_strdup((*argv)[i]);
		if (!new_argv[i])
			return (free_matrix(&new_argv), false);
	}
	j = -1;
	while (replace[++j])
	{
		new_argv[i] = ft_strdup(replace[j]);
		if (!new_argv[i++])
			return (free_matrix(&new_argv), false);
	}
	j = replace_index;
	while ((*argv)[++j])
	{
		new_argv[i] = ft_strdup((*argv)[j]);
		if (!new_argv[i++])
			return (free_matrix(&new_argv), false);
	}
	free_matrix(argv);
	free_matrix(&replace);
	*argv = new_argv;
	return (true);
}



bool	open_wildcards(char	***argv)
{
	int		i;
	char	*dir;
	char	*word;
	char	**replace;

	i = -1;
	while ((*argv)[++i])
	{
		if (!find_directory_and_word((*argv)[i], &dir, &word))
			return (false);
		if (!open_directory(dir, word, &replace))
			return (free(word), free(dir), false);
		free(word);
		free(dir);
		if (!integration(argv, replace, i))
			return (free_matrix(&replace), false);
	}
	return (true);
}
