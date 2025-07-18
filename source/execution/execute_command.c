/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 21:53:17 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/18 14:33:31 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "execute.h"

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

bool	add_cmd_to_path(char **paths, const char *cmd)
{
	int		i;
	char	*temp;
	char	*joined;

	if (!cmd)
		return (false);
	temp = ft_strjoin("/", cmd);
	if (!temp)
		return (false);
	i = -1;
	while (paths[++i])
	{
		joined = ft_strjoin(paths[i], temp);
		if (!joined)
			return (free(temp), false);
		free(paths[i]);
		paths[i] = joined;
	}
	free(temp);
	return (true);
}

char	*find_command_path(const char *cmd, t_env *env)
{
	t_env_node	*path;
	char		**bins;
	char		*cmd_path;

	path = env_get(env, "PATH");
	if (!path)
		return (NULL);
	bins = ft_split(path->value, ':');
	if (!bins || !add_cmd_to_path(bins, cmd))
		return (NULL);
	cmd_path = command_search(bins);
	free_matrix(&bins);
	return (cmd_path);
}

int	execute_command(t_ast *node, t_env *env, bool has_forked)
{
	pid_t	pid;
	char	**argv;
	int		status;
	char	*cmd_path;
	char	**envp;

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
			cmd_path = find_command_path(argv[0], env);
			if (!cmd_path)
			{
				printf("%s: command not found\n", argv[0]);
				exit(127);
			}
			envp = convert_env_to_matrix(env);
			execve(cmd_path, argv, envp);
			perror("execve failed");
			free(cmd_path);
			free_matrix(&envp);
			exit(126);
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
