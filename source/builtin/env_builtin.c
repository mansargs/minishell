/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:49:52 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/11 18:22:13 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_env(t_env *env)
{
	t_env_node	**all_vars;
	int			count;
	int			i;

	all_vars = get_all_env(env, &count);
	i = 0;
	while (i < count)
	{
		if (all_vars[i]->is_equal)
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

void	env_builtin(char **args, t_env *env)
{
	if (args[1])
	{
		printf("minishell: env: too many arguments\n");
		return ;
	}
	print_env(env);
	return ;
}
