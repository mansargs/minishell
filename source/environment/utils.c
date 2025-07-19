/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 23:21:59 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/19 09:19:26 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	count_env_vars(t_env *env)
{
	int				count;
	int				i;
	t_env_node		*node;

	count = 0;
	i = 0;
	while (i < ENV_TABLE_SIZE)
	{
		node = env->env[i];
		while (node)
		{
			count++;
			node = node->next;
		}
		i++;
	}
	return (count);
}

void	free_env_table(t_env *env)
{
	t_env_node	*current;
	t_env_node	*next;
	int			i;

	i = 0;
	while (i < HASH_SIZE)
	{
		current = env->env[i];
		while (current)
		{
			next = current->next;
			free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			current = next;
		}
		i++;
	}
	free(env);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
