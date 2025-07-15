/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:08:42 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/15 15:46:45 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	count_args(t_token *cmd)
{
	const t_token	*temp;
	int				count;

	count = 1;
	temp = cmd->next_token;
	while (temp)
	{
		++count;
		temp = temp->next_token;
	}
	return (count);
}

bool	fill_arguments(t_token *cmd, char **argv, int argc)
{
	const t_token	*temp;
	int				i;

	temp = cmd;
	i = -1;
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
		temp =temp->next_token;
	}
	argv[argc] = NULL;
	return (true);
}

char	**get_args(t_ast *node)
{
	char	**arguments;
	int		argc;

	argc = count_args(node->cmd);
	arguments = ft_calloc(argc + 1, sizeof(char *));
	if (!arguments || !fill_arguments(node->cmd, arguments, argc))
		return (NULL);
	return (arguments);
}

// int	execute_command(t_ast *node, t_env *env, bool has_forked)
// {
// 	pid_t	cmd;

// 	if (!has_forked)
// 	{
// 		is_builtin()
// 	}
// }
