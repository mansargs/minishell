/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 21:53:17 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/09 19:44:27 by mansargs         ###   ########.fr       */
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

static int	handle_fork_result(pid_t pid, char **argv, t_env *env, t_ast *node)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (open_redirects(node, env->shell) == FUNCTION_FAIL)
			exit(1);
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
	i = 0;
	while (argv[i] && argv[i][0] == '\0')
		++i;
	if (!argv[i])
		return (free_matrix(&argv), FUNCTION_SUCCESS);
	status = execute_builtin(argv, i, env, has_forked);
	if (env->is_builtin)
		return (free_matrix(&argv), status);
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		free_matrix(&argv);
		return (FUNCTION_FAIL);
	}
	return (handle_fork_result(pid, argv, env, node));
}

int	execute_command(t_ast *node, t_env *env, bool has_forked)
{
	int	result;
	int	old_stdin_stdout[2];

	old_stdin_stdout[0] = dup(STDIN_FILENO);
	old_stdin_stdout[1] = dup(STDOUT_FILENO);
	if (has_forked)
	{
		if (open_redirects(node, env->shell) == FUNCTION_FAIL)
			exit(1);
		return (execute_command_no_fork(node, env, has_forked));
	}
	else
	{
		result = execute_command_with_fork(node, env, has_forked);
		restore_standard_fd(old_stdin_stdout[0], old_stdin_stdout[1]);
		return (result);
	}
}
