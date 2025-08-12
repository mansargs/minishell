/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_no_fork.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 06:04:11 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/12 14:27:21 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	print_exec_error(char *cmd, int exit_code)
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

static bool	is_directory(char *cmd_path, char **argv, int cmd_pos, char ***envp)
{
	struct stat	st;

	if (stat(cmd_path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(argv[cmd_pos], STDERR_FILENO);
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
		free(cmd_path);
		free_matrix(envp);
		return (true);
	}
	return (false);
}

void	reclaim_child_resources(t_shell *shell, char **argv)
{
	close(shell->my_env->old_stdin);
	close(shell->my_env->old_stdout);
	close(shell->history.fd);
	free_matrix(&argv);
	free_env_table(shell->my_env);
	shell->my_env = NULL;
	conditional_free(&shell, true, true);
}

int	child_execute(char **argv, int cmd_pos, t_env *env)
{
	char	*cmd_path;
	char	**envp;
	int		exit_code;

	cmd_path = find_command_path(argv[cmd_pos], env);
	if (!cmd_path)
	{
		exit_code = env->exit_code;
		print_exec_error(argv[cmd_pos], env->exit_code);
		reclaim_child_resources(env->shell, argv);
		exit(exit_code);
	}
	envp = convert_env_to_matrix(env);
	if (is_directory(cmd_path, argv, cmd_pos, &envp))
	{
		reclaim_child_resources(env->shell, argv);
		exit(126);
	}
	execve(cmd_path, argv + cmd_pos, envp);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(argv[cmd_pos], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	free(cmd_path);
	free_matrix(&envp);
	exit(126);
}

bool	handle_empty_command(char **argv, t_env *env)
{
	int	i;

	i = 0;
	while (argv[i] && argv[i][0] == '\0')
	{
		if (i == env->empty_quote_pos)
		{
			env->exit_code = 127;
			ft_putendl_fd("minishell: : command not found", STDERR_FILENO);
			free_matrix(&argv);
			return (true);
		}
		++i;
	}
	if (!argv[i])
	{
		free_matrix(&argv);
		return (true);
	}
	return (false);
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
	if (handle_empty_command(argv, env))
		return (env->exit_code);
	i = 0;
	while (argv[i] && argv[i][0] == '\0')
		++i;
	result = execute_builtin(argv, i, env, has_forked);
	if (env->is_builtin)
		return (free_matrix(&argv), result);
	else
	{
		child_execute(argv, i, env);
		exit(EXIT_FAILURE);
	}
}
