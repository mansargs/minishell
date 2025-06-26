/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 02:47:43 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/27 02:29:08 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static char	*get_file_name(unsigned int *number)
{
	char	*num_by_string;
	char	*file_name;
	int		restore_errno;

	restore_errno = errno;
	while (1)
	{
		num_by_string = ft_itoa(*number);
		if (!num_by_string)
			return (NULL);
		file_name = ft_strjoin("heredoc_", num_by_string);
		free(num_by_string);
		if (access(file_name, F_OK))
			break ;
		free(file_name);
		++*number;
	}
	errno = restore_errno;
	return (file_name);
}

static void read_from_stdin(const int fd, const char *delim)
{
	char	*line;
	size_t	len;

	while (1)
	{
		ft_putstr_fd(" > ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return ;
		len = ft_strlen(line);
		if (len > 0 && line[len -1] == '\n')
			line[--len] = '\0';
		if (len == ft_strlen(delim) && ft_strncmp(line, delim, ft_strlen(delim)) == 0)
		{
			free(line);
			return ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

char *open_heredoc(const t_token *tokens, unsigned int *index)
{
	int		fd;
	char	*name;

	if (!tokens->next_token)
		return (printf("%s `newline'\n", SYN_ERR), NULL);
	name = get_file_name(index);
	if (!name)
		return (NULL);
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (free(name), NULL);
	read_from_stdin(fd, tokens->next_token->token_data);
	close(fd);
	return (name);
}
