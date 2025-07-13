/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:32:20 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/13 13:00:53 by alisharu         ###   ########.fr       */
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

char	**token_list_to_array(t_token *token)
{
	t_token	*tmp;
	char	**arr;
	int		len;
	int		i;

	len = 0;
	tmp = token;
	while (tmp)
	{
		len++;
		tmp = tmp->next_token;
	}
	arr = malloc(sizeof(char *) * (len + 1));
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
		free_array(args);
	}
	if (ft_strncmp(cmd->token_data, "unset", ft_strlen("unset")) == 0)
	{
		args = token_list_to_array(cmd);
		unset_builtin(args, env);
		free_array(args);
	}
	if (ft_strncmp(cmd->token_data, "env", ft_strlen("env")) == 0)
	{
		args = token_list_to_array(cmd);
		env_builtin(args, env);
		free_array(args);
	}
	if (ft_strncmp(cmd->token_data, "pwd", ft_strlen("pwd")) == 0)
	{
		args = token_list_to_array(cmd);
		pwd_builtin(shell);
		free_array(args);
	}
	if (ft_strncmp(cmd->token_data, "cd", ft_strlen("cd")) == 0)
	{
		args = token_list_to_array(cmd);
		cd_builtin(args, env);
		free_array(args);
	}
	if (ft_strncmp(cmd->token_data, "echo", ft_strlen("echo")) == 0)
	{
		args = token_list_to_array(cmd);
		echo_builtin(args, env);
		free_array(args);
	}
}
