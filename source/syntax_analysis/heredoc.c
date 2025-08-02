/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 02:47:43 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/02 20:47:14 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static char	*read_using_readline(int count_lines, const char *delim)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		printf("minishell: warning: here-document at line %d "
			"delimited by end-of-file (wanted `%s')\n", count_lines, delim);
		return (NULL);
	}
	return (line);
}

static void	read_from_stdin(t_shell *shell, const int fd, const char *delim,
	const int fd_history)
{
	size_t	len;
	int		count_lines;
	char	*line;

	count_lines = 0;
	while (1)
	{
		line = read_using_readline(count_lines, delim);
		if (!line)
			return ;
		++count_lines;
		ft_putendl_fd(line, fd_history);
		len = ft_strlen(line);
		if (len == ft_strlen(delim)
			&& ft_strncmp(line, delim, len) == 0)
		{
			free(line);
			return ;
		}
		handle_heredoc_open_quote(shell, line, fd);
		free(line);
	}
}

static int	fork_heredoc_reader(t_shell *shell, const t_token *token,
	const int fd, const int fd_history)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid < 0)
		return (perror("fork failed"), -1);
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		read_from_stdin(shell, fd, token->next_token->token_data, fd_history);
		close(fd);
		exit(0);
	}
	if (waitpid(pid, &status, 0) == -1)
		return (perror("waiting failed"), -1);
	if (WIFSIGNALED(status))
	{
		if (status == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		return (g_received_signal = WTERMSIG(status), -1);
	}
	return (0);
}

char	*open_heredoc(t_shell *shell, const t_token *token,
	const int fd_history)
{
	int		fd;
	char	*name;

	if (token->file_name)
		return (token->file_name);
	if (!token->next_token)
		return (printf("%s `newline'\n", SYN_ERR), NULL);
	name = get_file_name();
	if (!name)
		return (NULL);
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (free(name), NULL);
	if (fork_heredoc_reader(shell, token, fd, fd_history) == -1)
		return (free(name), NULL);
	return (name);
}
