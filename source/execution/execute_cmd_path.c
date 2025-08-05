/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:22:37 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/05 13:33:19 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	check_path_without_command(const char *cmd)
{
	char	*slash;
	char	*path;

	slash = ft_strrchr(cmd, '/');
	if (!slash)
		return (0);
	path = ft_substr(cmd, 0, slash - cmd + 1);
	if (!path)
		return (0);
	if (access(path, F_OK) != 0)
		return (free(path), 127);
	if (access(path, X_OK) != 0)
		return (free(path), 126);
	return (free(path), 0);
}

static int	check_and_set_exit_code(const char *cmd, t_env *env)
{
	int	ret;

	ret = check_path_without_command(cmd);
	if (ret)
		env->shell->exit_code = ret;
	else if (access(cmd, F_OK) != 0)
		env->shell->exit_code = 127;
	else if (access(cmd, X_OK) != 0)
		env->shell->exit_code = 126;
	else
		return (0);
	return (env->shell->exit_code);
}

static char	*find_command_path_with_slash(const char *cmd, t_env *env)
{
	if (check_and_set_exit_code(cmd, env) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

static char	*find_command_path_in_path(const char *cmd, t_env *env)
{
	t_env_node	*path_node;
	char		**bins;
	char		*cmd_path;

	path_node = env_get(env, "PATH");
	if (!path_node)
	{
		env->shell->exit_code = 127;
		return (NULL);
	}
	bins = ft_split(path_node->value, ':');
	if (!bins || !add_cmd_to_path(bins, cmd))
	{
		env->shell->exit_code = 127;
		free_matrix(&bins);
		return (NULL);
	}
	cmd_path = command_search(bins, env);
	free_matrix(&bins);
	if (!cmd_path)
		env->shell->exit_code = 127;
	return (cmd_path);
}

char	*find_command_path(const char *cmd, t_env *env)
{
	if (ft_strchr(cmd, '/'))
		return (find_command_path_with_slash(cmd, env));
	else
		return (find_command_path_in_path(cmd, env));
}
