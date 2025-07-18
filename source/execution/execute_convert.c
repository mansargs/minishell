/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_convert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:11:41 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/18 14:50:51 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

bool	fill_arguments(t_token *cmd, char **argv, int argc)
{
	const t_token	*temp ;
	int				i;

	i = -1;
	temp = cmd;
	while (temp)
	{
		++i;
		argv[i] = ft_strdup(temp->token_data);
		if (!argv[i])
		{
			while (--i >= 0)
				free(argv[i]);
			return (false);
		}
		temp = temp->next_token;
	}
	argv[argc] = NULL;
	return (true);
}

char	**get_arguments(t_token *cmd)
{
	char	**arguments;
	int		argc;

	if (!cmd)
		return (NULL);
	argc = count_args(cmd);
	arguments = ft_calloc(argc + 1, sizeof(char *));
	if (!arguments || !fill_arguments(cmd, arguments, argc))
	{
		free(arguments);
		return (NULL);
	}
	return (arguments);
}

char	*command_search(char **paths)
{
	int	i;

	i = -1;
	while (paths[++i])
	{
		if (access(paths[i], F_OK | X_OK) == 0)
			return (ft_strdup(paths[i]));
	}
	return (NULL);
}

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

char	**convert_env_to_matrix(t_env *env)
{
	char		**envp;
	int			count;
	int			i;
	int			index;
	t_env_node	*node;

	count = count_env_vars(env);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	i = 0;
	index = 0;
	while (i < ENV_TABLE_SIZE)
	{
		node = env->env[i];
		while (node)
		{
			envp[index++] = join(node->key, "=", node->value);
			node = node->next;
		}
		i++;
	}
	envp[index] = NULL;
	return (envp);
}
