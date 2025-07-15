/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:08:42 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/16 02:05:49 by mansargs         ###   ########.fr       */
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

bool	find_command_path(const char *cmd, t_env *env)
{
	t_env_node	*path;
	

	path = env_get(env, "PATH");
	if (!path)
		return (-1);


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
	{
		free_argv()
	}
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
