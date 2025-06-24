/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 02:47:43 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/25 02:50:00 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static int	count_heredocs(t_token *tokens)
{
	int		count;
	t_token	*temp;

	temp = tokens;
	count = 0;
	while (temp)
	{
		if (!ft_strncmp(temp->token_data, "<<", 2))
			if (temp->next_token)
				++count;
		temp = temp->next_token;
	}
	return (count);
}

static char	*get_file_name(const int number)
{
	char	*num_by_string;
	char	*file_name;

	num_by_string = ft_itoa(number);
	if (!num_by_string)
		return (NULL);
	file_name = ft_strjoin("heredoc_", num_by_string);
	free(num_by_string);
	return (file_name);
}

static void read_from_stdin(const int fd, const char *delim)
{
	char	*line;
	int		len;

	while (1)
	{
		ft_putstr_fd(" > ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return ;
		len = ft_strlen(line);
		if (line[len -1] == '\n')
			line[len -1] = '\0';
		if (!ft_strncmp(line, delim, len - 1))
		{
			free(line);
			return ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

static bool	open_heredoc_file(char *name, int *fd, int index)
{
	int	i;

	fd[index] = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	unlink(name);
	if (fd[index] == -1)
	{
		i = -1;
		while (++i < index)
			close(fd[i]);
		return (false);
	}
	return (true);
}

static bool	process_single_heredoc(t_token *token, int *fd, int index)
{
	char	*name;

	name = get_file_name(index + 1);
	if (!name)
		return (false);
	if (!open_heredoc_file(name, fd, index))
		return (free(name), false);
	free(name);
	read_from_stdin(fd[index], token->next_token->token_data);
	return (true);
}

int	*heredoc(t_token *tokens)
{
	int		*fd;
	int		count;
	int		index;
	t_token	*move;

	count = count_heredocs(tokens);
	if (count == 0)
		return (NULL);
	fd = (int *)ft_calloc(count, sizeof(int));
	if (!fd)
		return (NULL);
	index = 0;
	move = tokens;
	while (move)
	{
		if (!ft_strncmp(move->token_data, "<<", 2) && move->next_token)
		{
			if (!process_single_heredoc(move, fd, index))
				return (free(fd), NULL);
			++index;
		}
		move = move->next_token;
	}
	return (fd);
}
