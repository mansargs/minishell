/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:36:43 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/11 17:49:24 by alisharu         ###   ########.fr       */
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

void	unset_builtin(char **args, t_env *env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", args[i]);
			i++;
			continue ;
		}
		remove_env_key(env, args[i]);
		i++;
	}
}
