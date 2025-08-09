/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:25 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/09 19:48:12 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

volatile sig_atomic_t	g_received_signal;

static void	cleanup_heredoc_tempfiles(void)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
		return ;
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (ft_strncmp(entry->d_name, ".heredoc_", 9) == 0)
			unlink(entry->d_name);
	}
	closedir(dir);
}

static void	process_line(t_shell *shell, char *line)
{
	shell->tokens = tokenize(line, &shell->mem_error);
	if (!shell->tokens)
	{
		free(line);
		if (!shell->mem_error)
			return ;
		free_shell(&shell);
		exit(ENOMEM);
	}
	add_history(line);
	if (!valid_line(shell, &line))
	{
		free_tokens(&shell->tokens);
		free(line);
		return ;
	}
	free(line);
	shell->tree = building_ast(shell->tokens);
	if (!shell->tree)
	{
		free_shell(&shell);
		exit(ENOMEM);
	}
	shell->my_env->exit_code= execute_ast(shell->tree, shell->my_env, false);
	conditional_free(&shell, true, false);
}

void	run_shell_interactive(t_shell *shell)
{
	char	*line;
	char	*prompt;

	while (1)
	{
		setup_signals();
		prompt = ps_path(shell);
		cleanup_heredoc_tempfiles();
		line = readline(prompt);
		free(prompt);
		if (!line)
			break ;
		if (g_received_signal)
		{
			shell->my_env->exit_code= g_received_signal + 128;
			g_received_signal = 0;
		}
		process_line(shell, line);
	}
}
void	run_shell_noninteractive(t_shell *shell)
{
	char	*line;

	line = NULL;
	while (1)
	{
		cleanup_heredoc_tempfiles();
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		process_line(shell, line);
		line = NULL;
	}
}


int	main(int argc, char *argv[], char **envp)
{
	t_shell		*shell;

	(void)argv;
	if (argc > 1)
		return (ft_putendl_fd("This program must be run without any arguments.",
				STDERR_FILENO), EXIT_FAILURE);
	shell = init_shell(envp);
	if (!shell)
		return (ENOMEM);
	if (!init_env(shell, envp))
		return (ft_putendl_fd("Failed to initialize env table.", STDERR_FILENO),
			free_tokens(&shell->tokens), free_shell(&shell), ENOMEM);
	shell->interactive_mode = isatty(STDIN_FILENO);
	if (shell->interactive_mode)
		run_shell_interactive(shell);
	else
		run_shell_noninteractive(shell);
	rl_clear_history();
	if (shell->interactive_mode)
		printf("exit\n");
	conditional_free(&shell, true, true);
	return (0);
}
