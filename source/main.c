/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:25 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/02 00:53:56 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

volatile sig_atomic_t g_received_signal;


void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	free(shell->pwd);
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->history.fd >= 0)
		close(shell->history.fd);
	free(shell);
}

void	print_list(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->tokens;
	while (tmp != NULL)
	{
		printf("%s -> ", tmp->token_data);
		tmp = tmp -> next_token;
	}
	printf("NULL\n");
}

bool	only_spaces(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!is_space(str[i]))
			return (false);
	}
	return (true);
}

void	print_env_table(t_env *env)
{
	int				i;
	t_env_node		*node;

	i = 0;
	while (i < HASH_SIZE)
	{
		node = env->env[i];
		// if (node)
		// 	printf("Index %d:\n", i);
		while (node)
		{
			printf("  \033[34m%s\033[0m", node->key);
			if (node->is_equal)
			{
				printf("\033[37m=\033[0m");
				if (node->value)
					printf("\033[32m%s\033[0m", node->value);
			}
			printf("\n");
			node = node->next;
		}
		i++;
	}
}
int	main(int argc, char *argv[], char **envp)
{
	char	*line;
	t_shell	*shell;
	t_env	*my_env;
	t_ast	*tree;

	(void)argv;
	if (argc > 1)
	{
		printf("This program must be run without any arguments.\n");
		return (EXIT_FAILURE);
	}

	shell = init_shell(envp);
	if (!shell)
		return (EXIT_FAILURE);

	my_env = init_env(shell, envp);
	if (!my_env)
	{
		printf("Failed to initialize env table.\n");
		free_shell(shell);
		return (EXIT_FAILURE);
	}

	while (1)
	{
		setup_signals();
		line = readline("minishell$ ");
		if (!line)
			break;

		if (g_received_signal)
		{
			shell->exit_code = g_received_signal + 128;
			g_received_signal = 0;
		}

		shell->tokens = tokenize(line);
		if (!shell->tokens)
		{
			free(line);
			continue;
		}

		add_history(line);
		if (shell->tokens && !valid_line(shell, &line))
		{
			free_tokens(shell->tokens);
			shell->tokens = NULL;
			free(line);
			continue;
		}

		if (!(tree = building_ast(shell->tokens)))
		{
			free_tokens(shell->tokens);
			shell->tokens = NULL;
			free(line);
			return (EXIT_FAILURE);
		}
		execute_ast(tree, my_env, 0);

		free_ast(tree);
		free_tokens(shell->tokens);
		shell->tokens = NULL;
		free(line);
	}

	free_env_table(my_env);
	free_shell(shell);
	printf("exit\n");
	return (0);
}
