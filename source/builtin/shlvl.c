/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:49:14 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/03 21:18:24 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	shlvl(t_env *env)
{
	t_env_node	*node;
	int			shlvl_count;
	char		*new_value;

	node = env_get(env, "SHLVL");
	if (!node || !node->value)
		shlvl_count = 1;
	else
		shlvl_count = ft_atoi(node->value);
	shlvl_count++;
	if (shlvl_count < 0)
		shlvl_count = 0;
	if (shlvl_count >= 1000)
	{
		printf("minishell: warning: shell level (%d", shlvl_count);
		printf(") too high, resetting to 1\n");
		shlvl_count = 1;
	}
	new_value = ft_itoa(shlvl_count);
	if (!new_value)
		return (false);
	env_set(env, "SHLVL", new_value, true);
	free(new_value);
	return (true);
}
