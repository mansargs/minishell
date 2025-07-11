/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 23:25:43 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/11 12:49:03 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_sorted_export(t_env *env)
{
	t_env_node	**all_vars;
	int			count;
	int			i;

	all_vars = get_all_env(env, &count);
	sort_env_nodes(all_vars, count);
	i = 0;
	while (i < count)
	{
		if (all_vars[i]->is_equal)
		{
			if (all_vars[i]->value)
				printf("declare -x %s=\"%s\"\n", all_vars[i]->key,
					all_vars[i]->value);
			else
				printf("declare -x %s=\"\"\n", all_vars[i]->key);
		}
		else
			printf("declare -x %s\n", all_vars[i]->key);
		i++;
	}
	free(all_vars);
}
