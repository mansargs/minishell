/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 21:53:17 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/11 02:47:35 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	handle_child_status(int status, t_env *env)
{
	int	sig;

	if (WIFEXITED(status))
		env->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		env->exit_code = sig + 128;
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (sig == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
	}
	return (env->exit_code);
}

static int	handle_fork_result(pid_t pid, char **argv, t_env *env)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_execute(argv, env);
	}
	else
	{
		waitpid(pid, &status, 0);
		free_matrix(&argv);
		handle_child_status(status, env);
	}
	return (env->exit_code);
}

static int	execute_command_with_fork(t_ast *node, t_env *env, bool has_forked)
{
	pid_t	pid;
	int		status;
	char	**argv;
	int		i;

	argv = get_arguments(node->cmd, env);
	if (!argv)
		return (FUNCTION_FAIL);
	if (!open_wildcards(&argv))
		return (free_matrix(&argv), FUNCTION_FAIL);
	if (handle_empty_command(argv, env))
		return (env->exit_code);
	i = 0;
	while (argv[i] && argv[i][0] == '\0')
		++i;
	status = execute_builtin(argv, i, env, has_forked);
	if (env->is_builtin)
		return (free_matrix(&argv), status);
	pid = fork();
	if (pid < 0)
		return (perror("fork failed"), free_matrix(&argv), FUNCTION_FAIL);
	return (handle_fork_result(pid, argv, env));
}

int	execute_command(t_ast *node, t_env *env, bool has_forked)
{
	if (has_forked)
		return (execute_command_no_fork(node, env, has_forked));
	else
		return (execute_command_with_fork(node, env, has_forked));
}
