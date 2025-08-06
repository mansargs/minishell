/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:49:52 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/06 18:11:10 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	print_env(t_env *env)
{
	t_env_node	**all_vars;
	int			count;
	int			i;

	all_vars = get_all_env(env, &count);
	i = 0;
	while (i < count)
	{
		if (all_vars[i]->has_equal_sign)
		{
			if (all_vars[i]->value)
				printf("%s=%s\n", all_vars[i]->key, all_vars[i]->value);
			else
				printf("%s=\n", all_vars[i]->key);
		}
		i++;
	}
	free(all_vars);
}

int	env_builtin(char **args, t_env *env)
{
	if (args[1])
	{
		ft_putendl_fd("minishell: env: too many arguments", STDERR_FILENO);
		return (FUNCTION_FAIL);
	}
	print_env(env);
	return (FUNCTION_SUCCESS);
}
