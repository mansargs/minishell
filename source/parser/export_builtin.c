/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:17:08 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/10 21:55:40 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

t_env_node	**gather_all_env(t_env *env, int *count)
{
	t_env_node	**list;
	t_env_node	*node;
	int			i;
	int			idx;

	list = malloc(sizeof(t_env_node *) * 1024);
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
	*count = idx;
	return (list);
}

void	handle_export_argument(char *arg, t_env *env)
{
	char	*key;
	char	*value;
	int		has_equal;

	has_equal = 0;
	if (ft_strchr(arg, '=') != NULL)
		has_equal = 1;
	key = get_key_data(arg);
	if (!is_valid_identifier(key))
	{
		printf("export: `%s`: not a valid identifier\n", arg);
		free(key);
		return ;
	}
	if (has_equal)
		value = get_value_data(arg);
	else
		value = NULL;
	env_set(env, key, value, has_equal);
	free(key);
	if (value)
		free(value);
}


void	print_sorted_export(t_env *env)
{
	t_env_node	**all_vars;
	int			count;
	int			i;

	all_vars = gather_all_env(env, &count);
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
