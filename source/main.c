/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:25 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/08 15:57:33 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

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

int	main(int argc, char *argv[], char **envp)
{
	char	*line;
	t_shell	*shell;

	(void)argv;
	if (argc > 1)
	{
		printf("This program must be run without any arguments.\n");
		return (EXIT_FAILURE);
	}
	shell = init_shell(envp);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		shell->tokens = tokenize(line);
		add_history(line);
		if (!valid_line(shell, &line))
		{
			free(line);
			continue ;
		}
		//print_list(shell);
		free(line);
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
	if (shell)
		free(shell);
	shell = NULL;
	printf("exit\n");
	return (0);
}
