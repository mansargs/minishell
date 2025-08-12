/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:53:47 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/09 23:46:27 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (false);
	i = 2;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

int	print_tilda(char **args, t_env *env)
{
	t_env_node	*home;
	char		*path;

	home = env_get(env, "HOME");
	if (!home || !home->value)
	{
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		env->exit_code = 1;
		return (FUNCTION_FAIL);
	}
	path = ft_strjoin(home->value, args[1] + 1);
	printf("%s\n", path);
	return (FUNCTION_SUCCESS);
}

int	echo_builtin(char **args, t_env *env)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	if (args[1] && ft_strcmp(args[1], "~") == 0)
		return (print_tilda(args, env));
	while (args[i] && is_n_flag(args[i]))
	{
		newline = false;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	env->exit_code = 0;
	return (FUNCTION_SUCCESS);
}
