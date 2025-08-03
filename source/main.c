/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:25 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/04 02:23:05 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

volatile sig_atomic_t	g_received_signal;

int	main(int argc, char *argv[], char **envp)
{
	char	*line;
	char	*prompt;
	t_shell	*shell;

	(void)argv;
	if (argc > 1)
		return (printf("This program must be run without any arguments.\n"),
			EXIT_FAILURE);

	shell = init_shell(envp);
	if (!shell)
		return (ENOMEM);

	if (!init_env(shell, envp))
		return (printf("Failed to initialize env table.\n"),
			free_tokens(&shell->tokens), free_shell(&shell), ENOMEM);

	while (1)
	{
		setup_signals();
		prompt = ps_path(shell);
		line = readline(prompt);
		free(prompt);
		if (!line)
			break ;
		if (g_received_signal)
		{
			shell->exit_code = g_received_signal + 128;
			g_received_signal = 0;
		}
		shell->tokens = tokenize(line, &shell->mem_error);
		if (!shell->tokens)
		{
			if (!shell->mem_error)
			{
				free(line);
				continue ;
			}
			return (free(line), free_shell(&shell), ENOMEM);
		}
		add_history(line);
		if (!valid_line(shell, &line))
		{
			free_tokens(&shell->tokens);
			free(line);
			continue ;
		}
		free(line);

		shell->tree = building_ast(shell->tokens);
		if (!shell->tree)
			return (free_shell(&shell), ENOMEM);

		execute_ast(shell->tree, shell->my_env, false);
		conditional_free(&shell, true, false);
	}
	conditional_free(&shell, true, true);
	printf("exit\n");
	return (0);
}
