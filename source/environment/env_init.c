/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:37:31 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/02 15:05:49 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_env_node	*create_env_node(char *key, char *value, bool has_equal_sign)
{
	t_env_node	*new;

	new = ft_calloc(1, sizeof(t_env_node));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (!new->key)
		return (free(new), NULL);
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
			return (free(new->key), free(new), NULL);
	}
	else
		new->value = NULL;
	new->has_equal_sign = has_equal_sign;
	return (new);
}

bool	update_env_node_value(t_env_node *current, char *value,
	bool has_equal_sign)
{
	if (current->value)
		free(current->value);
	if (value)
	{
		current->value = ft_strdup(value);
		if (!current->value)
			return (false);
	}
	else
		current->value = NULL;
	current->has_equal_sign = has_equal_sign;
	return (true);
}

bool	env_set(t_env *env, char *key, char *value, bool has_equal_sign)
{
	unsigned int	index;
	t_env_node		*current;
	t_env_node		*new_node;

	index = hash_key(key);
	current = env->env[index];
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (update_env_node_value(current, value, has_equal_sign));
		current = current->next;
	}
	new_node = create_env_node(key, value, has_equal_sign);
	if (!new_node)
		return (false);
	new_node->next = env->env[index];
	env->env[index] = new_node;
	return (true);
}

bool	env_init_from_envp(t_env *env, char **envp)
{
	int			i;
	char		*key;
	char		*value;
	t_env_flags	flags;

	i = -1;
	while (envp[++i])
	{
		key = get_key_data(envp[i]);
		value = get_value_data(envp[i], &flags.mem_error);
		if (!key || flags.mem_error)
			return (false);
		flags.has_equal_sign = (ft_strchr(envp[i], '=') != NULL);
		if (!env_set(env, key, value, flags.has_equal_sign))
			return (free(key), free(value), false);
		free(key);
		free(value);
	}
	return (true);
}

bool	init_env(t_shell *my_shell, char **envp)
{
	my_shell->my_env = ft_calloc(1, sizeof(t_env));
	if (!my_shell->my_env)
		return (false);
	if (!env_init_from_envp(my_shell->my_env, envp))
		return (false);
	my_shell->my_env->shell = my_shell;
	return (true);
}
