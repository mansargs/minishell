/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:32:20 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/10 21:50:47 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_string_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	**token_list_to_array(t_token *token)
{
	int		count;
	t_token *tmp;
	char	**arr;
	int		i;

	count = 0;
	tmp = token;
	while (tmp)
	{
		count++;
		tmp = tmp->next_token;
	}
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (token)
	{
		arr[i++] = ft_strdup(token->token_data);
		token = token->next_token;
	}
	arr[i] = NULL;
	return (arr);
}

void	handle_builtin_commands(t_shell *shell, t_env *env)
{
	t_token	*cmd;
	char	**args;

	cmd = shell->tokens;
	if (!cmd)
		return ;
	if (ft_strncmp(cmd->token_data, "export", ft_strlen("export")) == 0)
	{
		args = token_list_to_array(cmd);
		export_builtin(args, env);
		free_string_array(args);
	}
}
