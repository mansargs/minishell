/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_no_fork.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 06:04:11 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/09 19:44:27 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	print_exec_error(char *cmd, int exit_code)
{
	if (ft_strchr(cmd, '/'))
	{
		if (exit_code == 127)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		}
		else if (exit_code == 126)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putendl_fd(": Permission denied", STDERR_FILENO);
		}
	}
	else
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
}

static void	is_directory(char *cmd_path, char **argv, char ***envp)
{
	struct stat	st;

	if (stat(cmd_path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(argv[0], STDERR_FILENO);
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
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
		print_exec_error(argv[0], env->exit_code);
		exit(env->exit_code);
	}
	envp = convert_env_to_matrix(env);
	is_directory(cmd_path, argv, &envp);
	execve(cmd_path, argv, envp);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(argv[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	free(cmd_path);
	free_matrix(&envp);
	exit(126);
}

int	execute_command_no_fork(t_ast *node, t_env *env, bool has_forked)
{
	char	**argv;
	bool	result;
	int		i;

	argv = get_arguments(node->cmd, env);
	if (!argv)
		return (FUNCTION_FAIL);
	if (!open_wildcards(&argv))
		return (free(argv), FUNCTION_FAIL);
	i = 0;
	while (argv[i] && argv[i][0] == '\0')
		++i;
	if (!argv[i])
		return (free_matrix(&argv), FUNCTION_SUCCESS);
	result = execute_builtin(argv, i, env, has_forked);
	if (env->is_builtin)
		return (free_matrix(&argv), result);
	else
	{
		child_execute(argv + i, env);
		exit(EXIT_FAILURE);
	}
}
