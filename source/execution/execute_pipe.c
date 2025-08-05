/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:56:36 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/04 16:29:25 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	pipe_children(t_ast *node, t_env *env, int pipe_fds[2], bool left)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (left)
		dup2(pipe_fds[1], STDOUT_FILENO);
	else
		dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	if (left)
		exit(execute_ast(node->left_side, env, true));
	else
		exit(execute_ast(node->right_side, env, true));
}

int	execute_pipe(t_ast *node, t_env *env)
{
	int		pipe_fds[2];
	pid_t	pids[2];
	int		status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pipe(pipe_fds) == -1)
		return (FUNCTION_FAIL);
	pids[0] = fork();
	if (pids[0] < 0)
		return (perror("fork failed"), FUNCTION_FAIL);
	if (pids[0] == 0)
		pipe_children(node, env, pipe_fds, true);
	pids[1] = fork();
	if (pids[1] < 0)
		return (perror("fork failed"), FUNCTION_FAIL);
	if (pids[1] == 0)
		pipe_children(node, env, pipe_fds, false);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	waitpid(pids[0], &status, 0);
	handle_child_status(status, env);
	waitpid(pids[1], &status, 0);
	return (handle_child_status(status, env));
}
