/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:49:43 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/02 19:51:58 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	restore_standard_fd(int std_in, int std_out)
{
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	close(std_in);
	close(std_out);
}

bool	open_redirects(t_ast *node)
{
	int		fd;
	t_token	*redirect;

	if (!node->redir)
		return (true);
	redirect = node->redir;
	while (redirect)
	{
		if (redirect->token_redirect_type == REDIRECT_HEREDOC
			|| redirect->token_redirect_type == REDIRECT_IN)
		{
			fd = open(redirect->file_name, O_RDONLY);
			if (fd < 0)
				return (perror(redirect->file_name), false);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else
		{
			if (redirect->token_redirect_type == REDIRECT_OUT)
				fd = open(redirect->file_name, O_WRONLY | O_CREAT
						| O_TRUNC, 0644);
			else
				fd = open(redirect->file_name, O_WRONLY | O_CREAT \
						| O_APPEND, 0644);
			if (fd < 0)
				return (perror(redirect->file_name), false);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redirect = redirect->next_token;
	}
	return (true);
}

t_execute_status	execute_logic_and(t_ast *node, t_env *env)
{
	t_execute_status	left_return;

	left_return = execute_ast(node->left_side, env, false);
	if (left_return != BUILTIN_OK && left_return != EXECUTE_OK)
		return (left_return);
	return (execute_ast(node->right_side, env, false));
}

t_execute_status	execute_logic_or(t_ast *node, t_env *env)
{
	t_execute_status	left_return;

	left_return = execute_ast(node->left_side, env, false);
	if (left_return == BUILTIN_OK || left_return == EXECUTE_OK)
		return (left_return);
	return (execute_ast(node->right_side, env, false));
}


t_execute_status	execute_subshell(t_ast *node, t_env *env, bool has_forked)
{
	pid_t					pid;
	t_execute_status		result;
	int						status;

	status = 0;
	if (has_forked)
		return (execute_ast(node->left_side, env, true));
	pid = fork();
	if (pid < 0)
		return (perror("fork failed"), ANOTHER_FAIL);
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		result = execute_ast(node->left_side, env, true);
		exit(result);
	}
	if (waitpid(pid, &result, 0) == -1)
		return (perror("waiting failed"), -1);
	if (WIFEXITED(status))
		env->shell->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (status == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		env->shell->exit_code = WTERMSIG(status) + 128;
	}
	return (env->shell->exit_code);
}

t_execute_status	execute_pipe(t_ast *node, t_env *env)
{
	int		pipe_fds[2];
	pid_t	left;
	pid_t	right;
	int		left_status;
	int		right_status;

	if (pipe(pipe_fds) == -1)
		return (1);
	left = fork();
	if (left < 0)
		return (perror("fork failed"), 1);
	signal(SIGINT, SIG_IGN);
	if (left == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		exit(execute_ast(node->left_side, env, true));
	}
	right = fork();
	if (right < 0)
		return (perror("fork failed"), 1);
	if (right == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(pipe_fds[0], STDIN_FILENO);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		exit(execute_ast(node->right_side, env, true));
	}
	close(pipe_fds[0]);
	close(pipe_fds[1]);

	if (waitpid(left, &left_status, 0) == -1
		|| waitpid(right, &right_status, 0) == -1)
		return (perror("waiting failed"), 1);

	if (WIFSIGNALED(right_status))
	{
		if (right_status == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		return (128 + WTERMSIG(right_status));
	}
	if (WIFEXITED(right_status))
		return (WEXITSTATUS(right_status));
	return (0);
}

t_execute_status execute_ast(t_ast *node, t_env *env, bool has_forked)
{
	int					old_stdin;
	int					old_stdout;
	t_execute_status	result;

	if (!node || !node->cmd)
		return (EXECUTE_OK);
	old_stdin = dup(STDIN_FILENO);
	old_stdout = dup(STDOUT_FILENO);
	if (!open_redirects(node))
		return (restore_standard_fd(old_stdin, old_stdout), ANOTHER_FAIL);
	if (node->cmd->token_operator_type == OPERATOR_AND)
		result = execute_logic_and(node, env);
	else if (node->cmd->token_operator_type == OPERATOR_OR)
		result = execute_logic_or(node, env);
	else if (node->cmd->token_operator_type == OPERATOR_PIPE)
		result = execute_pipe(node, env);
	else if (node->cmd->token_paren_type == PAREN_OPEN)
		result = execute_subshell(node, env, has_forked);
	else
		result = execute_command(node, env, has_forked);
	restore_standard_fd(old_stdin, old_stdout);
	if (result == -1)
		return (-1);
	return (result);
}

