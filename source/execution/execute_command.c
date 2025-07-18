/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 21:53:17 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/18 16:20:49 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "execute.h"

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

int	child_execute(char **argv, t_env *env)
{
	char	*cmd_path;
	char	**envp;

	cmd_path = find_command_path(argv[0], env);
	if (!cmd_path)
	{
		fprintf(stderr, "%s: command not found\n", argv[0]);
		exit(127);
	}
	envp = convert_env_to_matrix(env);
	execve(cmd_path, argv, envp);
	perror("execve");
	free(cmd_path);
	free_matrix(&envp);
	exit(126);// es promiison denide i u is a directory tarberakna kam not a directory
}

int	execute_command(t_ast *node, t_env *env, bool has_forked)
{
	pid_t	pid;
	int		status;
	char	**argv;

	argv = get_arguments(node->cmd);
	if (!argv)
		return (-1);
	if (execute_builtin(argv, env))
		return (free_matrix(&argv), 0);
	if (has_forked)
	{
		child_execute(argv, env);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
		return (perror("fork failed"), free_matrix(&argv), -1);
	if (pid == 0)
		child_execute(argv, env);
	waitpid(pid, &status, 0);
	free_matrix(&argv);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

