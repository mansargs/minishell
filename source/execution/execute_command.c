/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 21:53:17 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/18 08:51:58 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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

char	*join(char *str1, char *str2, char *str3)
{
	char	*joined;
	size_t	len;

	len = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3) + 1;
	joined = malloc(len);
	if (!joined)
		return (NULL);
	ft_strcpy(joined, str1);
	ft_strcat(joined, str2);
	ft_strcat(joined, str3);
	return (joined);
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
		//printf("%s\n", path[i]);
	}
	return (free(new_cmd), true);
}

char	**convert_env_to_matrix(t_env *env)
{
	char		**envp;
	int			i;
	int			index;
	int			count;
	t_env_node	*node;

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
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	index = 0;
	i = 0;
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


void print_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[i])
	{
		printf("[%d]: %s\n", i, matrix[i]);
		i++;
	}
}

int	find_command_path(const char *cmd, t_env *env, char *const *argv)
{
	t_env_node	*path;
	char		**bin;
	char		*cmd_path;
	char		**new_envp;

	//(void)argv;
	path = env_get(env, "PATH");
	//printf("%s\n", path->value);
	if (!path)
		return (-1);
	bin = ft_split(path->value, ':');
	if (!bin)
		return (-1);
	if (!add_cmd_to_path(bin, cmd))
		return (-1);
	cmd_path = command_search(bin);
	if (!cmd_path)
		return (1);
	new_envp = convert_env_to_matrix(env);
	//print_matrix(new_envp);
	execve(cmd_path, argv, new_envp);
	return (0);
}

int	execute_command(t_ast *node, t_env *env, bool has_forked)
{
	pid_t	pid;
	char	**argv;
	int		status;

	argv = get_arguments(node->cmd);
	if (!argv)
		return (-1);
	if (execute_builtin(argv, env))
		return (free_matrix(&argv), 0);
	if (!has_forked)
	{
		pid = fork();
		if (pid < 0)
			return (perror("fork failed"), free_matrix(&argv), -1);
		else if (pid == 0)
		{
			if (find_command_path(argv[0], env, argv) != 0)
			{
				printf("%s: command not found\n", argv[0]);
				exit(127);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
			free_matrix(&argv);
			return (WEXITSTATUS(status));
		}
	}
	free_matrix(&argv);
	return (0);
}
