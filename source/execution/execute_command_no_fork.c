/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_no_fork.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 06:04:11 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/05 11:54:13 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	print_exec_error(const char *cmd, int exit_code)
{
	if (ft_strchr(cmd, '/'))
	{
		if (exit_code == 127)
			printf("minishell: %s: No such file or directory\n", cmd);
		else if (exit_code == 126)
			printf("minishell: %s: Permission denied\n", cmd);
	}
	else
		printf("%s: command not found\n", cmd);
}

static void	is_directory(char *cmd_path, char **argv, char ***envp)
{
	struct stat	st;

	if (stat(cmd_path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		printf("minishell : %s: is a directory\n", argv[0]);
		free(cmd_path);
		free_matrix(envp);
		exit(126);
	}
}

int	child_execute(char **argv, t_env *env)
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
	is_directory(cmd_path, argv, &envp);
	execve(cmd_path, argv, envp);
	printf("minishell : %s: %s\n", argv[0], strerror(errno));
	free(cmd_path);
	free_matrix(&envp);
	exit(126);
}

int	execute_command_no_fork(t_ast *node, t_env *env, bool has_forked)
{
	char	**argv;
	bool	result;
	bool	is_builtin;

	argv = get_arguments(node->cmd, env);
	if (!argv)
		return (FUNCTION_FAIL);
	if (!open_wildcards(&argv))
		return (free(argv), FUNCTION_FAIL);
	result = execute_builtin(argv, env, &is_builtin, has_forked);
	if (is_builtin)
		return (free_matrix(&argv), result);
	else
	{
		child_execute(argv, env);
		exit(EXIT_FAILURE);
	}
}
