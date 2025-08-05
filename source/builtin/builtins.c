/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:32:20 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/04 04:48:51 by mansargs         ###   ########.fr       */
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

bool	execute_builtin(char **argv, t_env *env, bool *is_builtin,
	bool has_forked)
{
	*is_builtin = true;
	if (!ft_strcmp("cd", argv[0]))
		return (cd_builtin(argv, env));
	if (!ft_strcmp("pwd", argv[0]))
		return (pwd_builtin(argv, env));
	if (!ft_strcmp("unset", argv[0]))
		return (unset_builtin(argv, env));
	if (!ft_strcmp("export", argv[0]))
		return (export_builtin(argv, env));
	if (!ft_strcmp("env", argv[0]))
		return (env_builtin(argv, env));
	if (!ft_strcmp("echo", argv[0]))
		return (echo_builtin(argv, env));
	if (!ft_strcmp("exit", argv[0]))
		return (exit_builtin(env->shell, argv, has_forked));
	if (!ft_strcmp("history", argv[0]))
		return (history_builtin());
	*is_builtin = false;
	return (false);
}
