/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:37:31 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/10 18:33:32 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	env_set(t_env *env, char *key, char *value, int is_equal)
{
	unsigned int	index;
	t_env_node		*current;
	t_env_node		*new_node;

	index = hash_key(key);
	current = env->env[index];
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0)
		{
			if (current->value)
				free(current->value);
			if (value)
				current->value = ft_strdup(value);
			else
				current->value = NULL;
			current->is_equal = is_equal;
			return ;
		}
		current = current->next;
	}
	new_node = malloc(sizeof(t_env_node));
	if (!new_node)
		return ;
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->is_equal = is_equal;
	new_node->next = env->env[index];
	env->env[index] = new_node;
}

void	env_init_from_envp(t_env *env, char **envp)
{
	int		i;
	char	*key;
	char	*value;
	int		has_equal;

	i = 0;
	while (envp[i])
	{
		key = get_key_data(envp[i]);
		value = get_value_data(envp[i]);
		has_equal = (ft_strchr(envp[i], '=') != NULL);
		env_set(env, key, value, has_equal);
		free(key);
		free(value);
		i++;
	}
}

t_env	*init_env(char **envp)
{
	t_env	*environment;
	int		i;

	environment = malloc(sizeof(t_env));
	if (!environment)
		return (NULL);
	i = 0;
	while (i < HASH_SIZE)
		environment->env[i++] = NULL;
	env_init_from_envp(environment, envp);
	return (environment);
}

