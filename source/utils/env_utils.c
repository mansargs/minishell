/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 03:58:18 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/04 05:00:47 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_env_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*get_env_value(char **envp, const char *str)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], str, len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
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
