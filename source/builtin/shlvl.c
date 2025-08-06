/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:49:14 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/06 18:21:04 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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
		ft_putstr_fd("minishell: warning: shell level (", STDERR_FILENO);
		ft_putnbr_fd(shlvl_count, STDERR_FILENO);
		ft_putendl_fd(") too high, resetting to 1", STDERR_FILENO);
		shlvl_count = 1;
	}
	new_value = ft_itoa(shlvl_count);
	if (!new_value)
		return (false);
	env_set(env, "SHLVL", new_value, true);
	free(new_value);
	return (true);
}
