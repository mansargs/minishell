/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:56:36 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/14 18:10:13 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	pipe_children(t_ast *node, t_env *env, int pipe_fds[2], bool left)
{
	int	result;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (left)
		dup2(pipe_fds[1], STDOUT_FILENO);
	else
		dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	if (env->old_stdin != STDIN_FILENO)
		close(env->old_stdin);
	if (env->old_stdout != STDOUT_FILENO)
		close(env->old_stdout);
	if (left)
	{
		result = execute_ast(node->left_side, env, true);
		free_all_data(env->shell, NULL);
		exit(result);
	}
	else
	{
		result = execute_ast(node->right_side, env, true);
		free_all_data(env->shell, NULL);
		exit(result);
	}
}
void	print_signaled_message(int status, t_env *env)
{
	if (!env->exit_code && WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(STDERR_FILENO, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
	}
}
int	execute_pipe(t_ast *node, t_env *env)
{
	int		pipe_fds[2];
	pid_t	pids[2];
	int		status[2];
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pipe(pipe_fds) == -1)
		return (FUNCTION_FAIL);
	pids[1] = fork();
	if (pids[1] < 0)
		return (perror("fork failed"), FUNCTION_FAIL);
	if (pids[1] == 0)
		pipe_children(node, env, pipe_fds, false);
	pids[0] = fork();
	if (pids[0] < 0)
		return (perror("fork failed"), FUNCTION_FAIL);
	if (pids[0] == 0)
		pipe_children(node, env, pipe_fds, true);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	waitpid(pids[1], &status[1], 0);
	handle_child_status(status[1], env);
	waitpid(pids[0], &status[0], 0);
	print_signaled_message(status[0], env);
	return (env->exit_code);
}
