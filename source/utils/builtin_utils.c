/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 23:56:05 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/05 11:20:59 by alisharu         ###   ########.fr       */
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
			printf("minishell: cd: HOME not set\n");
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
		printf("minishell: cd: too many arguments\n");
		return (0);
	}
	return (1);
}
