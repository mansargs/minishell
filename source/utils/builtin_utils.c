/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 23:56:05 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/06 19:29:57 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*handle_cd_without_dir(char **args, t_env *env)
{
	t_env_node	*home;

	if (!args[1])
	{
		home = env_get(env, "HOME");
		if (!home || !home->value)
		{
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
			return (NULL);
		}
		return (ft_strdup(home->value));
	}
	return (NULL);
}

int	check_too_many_dirs(char **args, t_env *env)
{
	int	count;

	(void)env;
	count = 0;
	while (args && args[count])
		count++;
	if (count > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (0);
	}
	return (1);
}

void	failed_chdir(t_env *env, char *path)
{
	if (errno == EACCES)
		env->shell->exit_code = 126;
	else
		env->shell->exit_code = 1;
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}
