/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:31:07 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/04 06:32:03 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

bool	collect_matched(char ***matched, const char *newly_added)
{
	char	**new_arg_list;
	int		count;

	if (!*newly_added)
		return (true);
	count = count_lines(*matched);
	new_arg_list = ft_calloc(count + 2, sizeof(char *));
	if (!new_arg_list)
		return (false);
	if (*matched)
		if (!copy_and_duplicate_old_args(new_arg_list, *matched))
			return (false);
	new_arg_list[count] = ft_strdup(newly_added);
	if (!new_arg_list[count])
		return (free_matrix(&new_arg_list), false);
	new_arg_list[count + 1] = NULL;
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
		if (!item)
			break ;
		if (!ft_strcmp(".", item->d_name) || !ft_strcmp("..", item->d_name))
			continue ;
		if (is_match(item->d_name, word))
			if (!collect_matched(incoming_arg, item->d_name))
				return (free_matrix(incoming_arg), closedir(dir_content),
					false);
	}
	closedir(dir_content);
	return (true);
}

static int	copy_before_and_replace(char **new_argv, char **argv,
				char **replace, int replace_index)
{
	int	i;
	int	j;

	i = 0;
	while (i < replace_index)
	{
		new_argv[i] = ft_strdup(argv[i]);
		if (!new_argv[i])
			return (-1);
		i++;
	}
	j = 0;
	while (replace[j])
	{
		new_argv[i] = ft_strdup(replace[j]);
		if (!new_argv[i])
			return (-1);
		i++;
		j++;
	}
	return (i);
}

bool	integration(char ***argv, char **replace, int replace_index)
{
	char	**new_argv;
	int		total_len;
	int		pos;

	if (!replace)
		return (true);
	total_len = count_lines(*argv) + count_lines(replace) + 1;
	new_argv = ft_calloc(total_len, sizeof(char *));
	if (!new_argv)
		return (false);
	pos = copy_before_and_replace(new_argv, *argv, replace, replace_index);
	if (pos == -1)
		return (free_matrix(&new_argv), false);
	while ((*argv)[replace_index + 1])
	{
		new_argv[pos] = ft_strdup((*argv)[replace_index + 1]);
		if (!new_argv[pos])
			return (free_matrix(&new_argv), false);
		pos++;
		replace_index++;
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
		if (ft_strchr((*argv)[i], '*') == 0)
			continue ;
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
