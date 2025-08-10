/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_convert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:11:41 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/11 02:16:20 by mansargs         ###   ########.fr       */
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

static bool all_is_quote(const char *line)
{
	if (!line || *line == '\0')
		return (false);
	while (*line)
	{
		if (*line != '\'' && *line != '"')
			return (false);
		++line;
	}
	return (true);
}


static char	**build_argv_from_tokens(t_env *env,
	t_token *cmd_tokens, char **envp)
{
	char	**argv;
	t_token	*arg;
	int		count;
	int		i;
	bool	only_quotes;

	count = count_tokens(cmd_tokens);
	argv = ft_calloc((count + 1), sizeof(char *));
	if (!argv)
		return (NULL);
	arg = cmd_tokens;
	i = 0;
	only_quotes = false;
	env->empty_quote_pos = -1;
	while (arg)
	{
		if (env->empty_quote_pos == -1 && all_is_quote(arg->token_data))
			only_quotes = true;
		if (arg->token_type == TOKEN_WORD)
		{
			if (handle_quots(env, envp, arg) == -1)
				return (free_matrix(&argv), NULL);
			if (arg->token_data[0] == '\0' && only_quotes)
				env->empty_quote_pos = i;
			argv[i++] = ft_strdup(arg->token_data);
		}
		arg = arg->next_token;
	}
	argv[i] = NULL;
	return (argv);
}

char	**get_arguments(t_token *cmd_tokens, t_env *env)
{
	char	**argv;
	char	**envp;

	envp = convert_env_to_matrix(env);
	if (!envp)
		return (NULL);
	argv = build_argv_from_tokens(env, cmd_tokens, envp);
	free_matrix(&envp);
	return (argv);
}

char	*command_search(char **paths, t_env *env)
{
	int	i;

	i = -1;
	while (paths[++i])
	{
		if (access(paths[i], F_OK) != 0)
			env->exit_code = 127;
		else if (access(paths[i], X_OK | R_OK) != 0)
			env->exit_code = 126;
		else if (access(paths[i], F_OK | X_OK) == 0)
			return (ft_strdup(paths[i]));
	}
	return (NULL);
}

char	**convert_env_to_matrix(t_env *env)
{
	char		**envp;
	int			count;
	int			i;
	int			index;
	t_env_node	*node;

	count = count_env_vars(env);
	envp = ft_calloc(count + 1, sizeof(char *));
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
