/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 02:47:43 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/02 00:49:06 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static int	get_random_number(void)
{
	int				fd;
	unsigned int	number;
	int				result;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (-1);
	result = read(fd, &number, sizeof number);
	close(fd);
	if (result == -1)
		return (-1);
	return (number);
}

static char	*get_file_name(void)
{
	char			*num_by_string;
	char			*file_name;
	unsigned int	number;

	while (1)
	{
		while (1)
		{
			number = get_random_number();
			if (number < INT_MAX)
				break ;
		}
		num_by_string = ft_itoa(number);
		if (!num_by_string)
			return (NULL);
		file_name = ft_strjoin(".heredoc_", num_by_string);
		free(num_by_string);
		if (access(file_name, F_OK) == -1)
			break ;
		free(file_name);
	}
	return (file_name);
}

static void	read_from_stdin(t_shell *shell, const int fd, const char *delim,
	const int fd_history)
{
	size_t	len;
	int		count_lines;
	int		copy_flag;
	char	*new_line;
	char	*line;

	count_lines = 0;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n",  count_lines, delim);
			return ;
		}
		++count_lines;
		ft_putendl_fd(line, fd_history);
		len = ft_strlen(line);
		if (len == ft_strlen(delim)
			&& ft_strncmp(line, delim, len) == 0)
		{
			free(line);
			return ;
		}
		if (ft_strchr(line, '$') && shell->heredoc_quote == 0)
		{
			copy_flag = 0;
			new_line = open_quotes(shell->envp, line, &copy_flag);
			ft_putendl_fd(new_line, fd);
			free(new_line);
		}
		else
			ft_putendl_fd(line, fd);
		free(line);
	}
}

char	*open_heredoc(t_shell *shell, const t_token *token, const int fd_history)
{
	int		fd;
	char	*name;
	pid_t	pid;
	int		status;

	status = 0;
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
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		return (NULL);
	}
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
		return (perror("waiting failed"), free(name), NULL);
	if (WIFSIGNALED(status))
	{
		if (status == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		g_received_signal = WTERMSIG(status);
		return (free(name), NULL);
	}
	return (name);
}
