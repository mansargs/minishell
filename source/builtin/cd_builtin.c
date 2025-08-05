/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:27:17 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/05 11:57:00 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*cd_tilda(char **args, t_env *env)
{
	t_env_node	*home;
	char		*path;

	home = env_get(env, "HOME");
	if (!home || !home->value)
	{
		printf("minishell: cd: HOME not set\n");
		env->shell->exit_code = 1;
		return (NULL);
	}
	path = ft_strjoin(home->value, args[1] + 1);
	return (path);
}

char	*cd_minus(char **args, t_env *env)
{
	t_env_node	*old_pwd;
	char		*path;

	old_pwd = env_get(env, "OLDPWD");
	if (!old_pwd || !old_pwd->value)
	{
		printf("minishell: cd: OLDPWD not set\n");
		env->shell->exit_code = 1;
		return (NULL);
	}
	path = ft_strjoin(old_pwd->value, args[1] + 1);
	return (path);
}

char	*cd_validation(char **args, t_env *env)
{
	char		*path;
	t_env_node	*home;

	if (!check_too_many_dirs(args, env))
		return (NULL);
	if (!args[1])
	{
		home = env_get(env, "HOME");
		if (!home || !home->value)
		{
			printf("minishell: cd: HOME not set\n");
			env->shell->exit_code = 1;
			return (NULL);
		}
		path = ft_strdup(home->value);
	}
	else if (args[1][0] == '~')
		path = cd_tilda(args, env);
	else if (args[1][0] == '-')
		path = cd_minus(args, env);
	else
		path = ft_strdup(args[1]);
	return (path);
}

static void	update_pwd_on_error(t_env *env)
{
	t_env_node	*pwd_node;

	printf("cd: error retrieving current directory: getcwd: ");
	printf("cannot access parent directories: No such file or directory\n");
	pwd_node = env_get(env, "PWD");
	if (env->shell->pwd)
		free(env->shell->pwd);
	if (!pwd_node || !pwd_node->value)
		env->shell->pwd = ft_strdup("");
	else
		env->shell->pwd = ft_strjoin(pwd_node->value, "/..");
	env_set(env, "PWD", env->shell->pwd, 1);
}

int	cd_builtin(char **args, t_env *env)
{
	char		*old_pwd;
	char		new_pwd[PATH_MAX];
	char		*path;
	t_env_node	*pwd_node;

	path = cd_validation(args, env);
	if (path == NULL)
		return (free(path), FUNCTION_FAIL);
	pwd_node = env_get(env, "PWD");
	if (pwd_node && pwd_node->value)
		old_pwd = pwd_node->value;
	if (chdir(path) != 0)
	{
		if (errno == EACCES)
			env->shell->exit_code = 126;
		else
			env->shell->exit_code = 1;
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		return (free(path), FUNCTION_FAIL);
	}
	if (!getcwd(new_pwd, sizeof(new_pwd)))
		return (free(path), update_pwd_on_error(env), false);
	env_set(env, "OLDPWD", old_pwd, 1);
	env_set(env, "PWD", new_pwd, 1);
	free(env->shell->pwd);
	env->shell->pwd = ft_strdup(new_pwd);
	free(path);
	return (FUNCTION_SUCCESS);
}
