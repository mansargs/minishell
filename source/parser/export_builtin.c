/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:17:08 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/11 12:58:24 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

unsigned int	hash_key(const char *key)
{
	unsigned int	hash;

	hash = 0;
	while (*key)
		hash = (hash * 31) + *key++;
	return (hash % HASH_SIZE);
}

void	sort_env_nodes(t_env_node **list, int count)
{
	int			i;
	int			j;
	t_env_node	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(list[j]->key, list[j + 1]->key) > 0)
			{
				tmp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

t_env_node	**get_all_env(t_env *env, int *count)
{
	t_env_node	**list;
	t_env_node	*node;
	int			i;
	int			idx;
	int			total;

	total = env_size(env);
	list = malloc(sizeof(t_env_node *) * total);
	if (!list)
		return (NULL);
	idx = 0;
	i = 0;
	while (i < HASH_SIZE)
	{
		node = env->env[i];
		while (node)
		{
			list[idx++] = node;
			node = node->next;
		}
		i++;
	}
	*count = total;
	return (list);
}

void	handle_export_argument(char *arg, t_env *env)
{
	char	*key;
	char	*value;
	int		is_equal;

	is_equal = 0;
	value = NULL;
	if (ft_strchr(arg, '=') != NULL)
		is_equal = 1;
	key = get_key_data(arg);
	if (!is_valid_identifier(key))
	{
		free(key);
		return ;
	}
	if (is_equal)
	{
		value = get_value_data(arg);
		env_set(env, key, value, 1);
	}
	else if (!env_get(env, key))
		env_set(env, key, NULL, 0);
	free(key);
	if (is_equal && value)
		free(value);
}

int	export_builtin(char **args, t_env *env)
{
	int	i;

	if (!args[1])
	{
		print_sorted_export(env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		handle_export_argument(args[i], env);
		i++;
	}
	return (0);
}
