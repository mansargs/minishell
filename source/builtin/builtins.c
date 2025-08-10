/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:32:20 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/11 02:03:32 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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
	arr = ft_calloc(len + 1, sizeof(char *));
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

bool	execute_builtin(char **argv, int cmd_pos, t_env *env, bool has_forked)
{
	env->is_builtin = true;
	if (!ft_strcmp("cd", argv[cmd_pos]))
		return (cd_builtin(argv + cmd_pos, env));
	if (!ft_strcmp("pwd", argv[cmd_pos]))
		return (pwd_builtin(argv + cmd_pos, env));
	if (!ft_strcmp("unset", argv[cmd_pos]))
		return (unset_builtin(argv + cmd_pos, env));
	if (!ft_strcmp("export", argv[cmd_pos]))
		return (export_builtin(argv + cmd_pos, env));
	if (!ft_strcmp("env", argv[cmd_pos]))
		return (env_builtin(argv + cmd_pos, env));
	if (!ft_strcmp("echo", argv[cmd_pos]))
		return (echo_builtin(argv + cmd_pos, env));
	if (!ft_strcmp("exit", argv[cmd_pos]))
		return (exit_builtin(env->shell, argv + cmd_pos, has_forked));
	if (!ft_strcmp("history", argv[cmd_pos]))
		return (history_builtin());
	env->is_builtin = false;
	return (false);
}
