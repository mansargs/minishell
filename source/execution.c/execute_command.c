/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:08:42 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/17 16:18:35 by mansargs         ###   ########.fr       */
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

void	free_matrix(char ***matrix)
{
	int i;

	if (!matrix || !*matrix)
		return;
	i = 0;
	while ((*matrix)[i])
	{
		free((*matrix)[i]);
		i++;
	}
	free(*matrix);
	*matrix = NULL;
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

char	**get_arguments(t_token *cmd)
{
	char	**arguments;
	int		argc;

	argc = count_args(cmd);
	arguments = ft_calloc(argc + 1, sizeof(char *));
	if (!arguments || !fill_arguments(cmd, arguments, argc))
		return (NULL);
	return (arguments);
}

bool	execute_builtin(char **argv, t_env *env)
{
	if (!ft_strcmp("cd", argv[0]))
		return (cd_builtin(argv, env), true);
	if (!ft_strcmp("pwd", argv[0]))
		return (pwd_builtin(NULL), true);
	if (!ft_strcmp("unset", argv[0]))
		return (unset_builtin(argv, env), true);
	if (!ft_strcmp("export", argv[0]))
		return (export_builtin(argv, env), true);
	if (!ft_strcmp("env", argv[0]))
		return (env_builtin(argv, env), true);
	// if (!ft_strcmp("echo", argv[0]))
	// 	return (echo_builtin(), true);
	// if (!ft_strcmp("exit", argv[0]))
	// 	return (exit_builtin(), true);
	return (false);
}

bool	add_cmd_to_path(char **path, const char *cmd)
{
	int		i;
	char	*new_cmd;
	char	*joined;

	new_cmd = ft_strjoin("/", cmd);
	if (!new_cmd)
		return (false);
	i = -1;
	while (path[++i])
	{
		joined = ft_strjoin(path[i], new_cmd);
		if (!joined)
			return (free(new_cmd), false);
		free(path[i]);
		path[i] = joined;
	}
	return (free(new_cmd), true);
}

char	*command_search(char	**path)
{
	int		i;

	i = -1;
	while (path[++i])
	{
		if (access(path[i], F_OK) == 0)
			return (path[i]);
	}
	return (NULL);
}


int	count_env_lines(t_env_node *env)
{
	const t_env_node	*temp;
	int					count;

	count = 0;
	temp = env;
	while (temp)
	{
		++count;
		temp = temp->next;
	}
	return (count);
}

bool	merge_key_and_value(const t_env_node *node, char **line)
{
	char	*key_equal;
	char	*full;

	if (node->is_equal)
	{
		key_equal = ft_strjoin(node->key, "=");
		if (!key_equal)
			return (false);
	full = ft_strjoin(key_equal, node->value);
	if (!full)
		return (free(key_equal), false);
	}
	else
	{
		full = ft_strdup(node->key);
		if (!full)
			return (false);
	}
	return (*line = full, true);
}

bool	fill_env_table(t_env_node *node, char **env_table)
{
	const t_env_node	*temp;
	int					i;

	temp = node;
	i = -1;
	while (temp)
	{
		++i;
		if (!merge_key_and_value(temp, env_table + i))
		{
			while (--i >= 0)
				free(env_table[i]);
			return (false);
		}
		temp = temp->next;
	}
	return (true);
}

char	**env_to_char_matrix(const t_env *env)
{
	char		**env_table;
	t_env_node	*move;
	int			lines;

	lines = count_env_lines(env->env);
	if (!lines)
		return (NULL);
	env_table = ft_calloc(lines + 1, sizeof(char *));
	if (!env_table)
		return (NULL);
	if (!fill_env_table(env->env, env_table))
		return (free_matrix(&env_table), NULL);
	env_table[lines] = NULL;
	return (env_table);
}

int	find_command_path(const char *cmd, t_env *env, const char **argv)
{
	t_env_node	*path;
	char		**bin;
	char		*cmd_path;
	char		**env_table;

	path = env_get(env, "PATH");
	printf("%s\n", path->value);
	if (!path)
		return (-1);
	bin = ft_split(path->value, ':');
	if (!bin)
		return (-1);
	if (!add_cmd_to_path(bin, cmd))
		return (-1);
	cmd_path = command_search(path);
	if (!cmd_path)
		return (1);
	execve(cmd_path, argv, );
	return (0);
}


int	execute_command(t_ast *node, t_env *env, bool has_forked)
{
	pid_t	cmd_pid;
	int		exit_code;
	char	**argv;

	argv = get_arguments(node->cmd);
	if (!argv)
		return (-1);
	if (execute_builtin(argv, env))
		return (free_matrix(&argv), 0);
	if (!execute_builtin(argv, env))
	{
		if (!has_forked)
		{
			cmd_pid = fork();
			if (cmd_pid < 0)
				return (perror("fork failed"), -1);

		}
	}
}
