/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 02:47:43 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/14 22:01:58 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static char	*read_using_readline(int count_lines, const char *delim)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document at line ",
			STDERR_FILENO);
		ft_putnbr_fd(count_lines, STDERR_FILENO);
		ft_putstr_fd("delimited by end-of-file (wanted `", STDERR_FILENO);
		ft_putstr_fd((char *)delim, STDERR_FILENO);
		ft_putendl_fd("')", STDERR_FILENO);
		return (NULL);
	}
	return (line);
}

void	handle_exit_and_quote(t_shell *shell, const int fd, char *line)
{
	char	*replaced;

	if (ft_strnstr(line, "$?", ft_strlen(line)) && shell->exit_code_flag == 0)
	{
		replaced = replace_exit_code(shell, line);
		ft_putendl_fd(replaced, fd);
		free(replaced);
	}
	else
		handle_heredoc_open_quote(shell, line, fd);
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
			break ;
		++count_lines;
		ft_putendl_fd(line, fd_history);
		len = ft_strlen(line);
		if (len == ft_strlen(delim)
			&& ft_strncmp(line, delim, len) == 0)
		{
			free(line);
			break ;
		}
		handle_exit_and_quote(shell, fd, line);
		free(line);
	}
	rl_clear_history();
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
		free_all_data(shell, NULL, true);
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

char	*open_heredoc(t_shell *shell, t_token *token,
	const int fd_history)
{
	int		fd;

	if (token->file_name)
		return (token->file_name);
	if (!token->next_token)
	{
		ft_putstr_fd(SYN_ERR, STDERR_FILENO);
		return (ft_putendl_fd(" `newline'", STDERR_FILENO), NULL);
	}
	token->file_name = get_file_name();
	if (!token->file_name)
		return (NULL);
	fd = open(token->file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (free(token->file_name), NULL);
	if (fork_heredoc_reader(shell, token, fd, fd_history) == -1)
		return (free(token->file_name), NULL);
	return (token->file_name);
}
