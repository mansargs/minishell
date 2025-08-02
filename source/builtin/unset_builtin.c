/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:36:43 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/02 19:33:57 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	remove_env_key(t_env *env, const char *key)
{
	unsigned int	index;
	t_env_node		*curr;
	t_env_node		*prev;

	index = hash_key(key);
	curr = env->env[index];
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				env->env[index] = curr->next;
			free(curr->key);
			if (curr->value)
				free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

t_execute_status	unset_builtin(char **args, t_env *env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			i++;
			continue ;
		}
		remove_env_key(env, args[i]);
		i++;
	}
	return (BUILTIN_OK);
}
