/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 21:53:17 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/02 03:07:52 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <errno.h>
#include <unistd.h>

static void	print_exec_error(const char *cmd, int exit_code)
{
	if (strchr(cmd, '/'))
	{
		if (exit_code == 127)
			printf("minishell: %s: No such file or directory\n", cmd);
		else if (exit_code == 126)
			printf("minishell: %s: Permission denied\n", cmd);
	}
	else
		printf("%s: command not found\n", cmd);
}

static int	child_execute(char **argv, t_env *env)
{
	char	*cmd_path;
	char	**envp;

	cmd_path = find_command_path(argv[0], env);
	if (!cmd_path)
	{
		print_exec_error(argv[0], env->shell->exit_code);
		exit(env->shell->exit_code);
	}
	envp = convert_env_to_matrix(env);
	execve(cmd_path, argv, envp);
	perror("execve");
	free(cmd_path);
	free_matrix(&envp);
	exit(126);
}

static int	execute_command_no_fork(t_ast *node, t_env *env)
{
	char	**argv;

	argv = get_arguments(node->cmd, env);
	if (!argv)
		return (-1);
	if (!open_wildcards(&argv))
		return (free(argv), -1);
	t_builtin_status ret = execute_builtin(argv, env);
	if (ret != NOT_BUILTIN)
	{
		free_matrix(&argv);
		env->shell->exit_code = ret;
		return (ret);
	}
	child_execute(argv, env);
	exit(EXIT_FAILURE);
}

static int	execute_command_with_fork(t_ast *node, t_env *env)
{
	pid_t	pid;
	int		status;
	char	**argv;

	argv = get_arguments(node->cmd, env);
	if (!argv)
		return (-1);
	if (!open_wildcards(&argv))
		return (free_matrix(&argv), -1);
	if (execute_builtin(argv, env))
		return (free_matrix(&argv), 0);
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		free_matrix(&argv);
		return (-1);
	}
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_execute(argv, env);
	}
	waitpid(pid, &status, 0);
	free_matrix(&argv);
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

int	execute_command(t_ast *node, t_env *env, bool has_forked)
{
	if (has_forked)
		return (execute_command_no_fork(node, env));
	else
		return (execute_command_with_fork(node, env));
}
