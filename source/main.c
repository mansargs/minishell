/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:25 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/02 21:46:42 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

void	print_tokens_with_neighbors(t_token *head)
{
	t_token *curr = head;
	int index = 0;

	while (curr != NULL)
	{
		printf("Token[%d]:\n", index++);
		printf("  token_data: %s\n", curr->token_data ? curr->token_data : "(null)");

		if (curr->prev_token)
			printf("  Prev token_data: %s\n", curr->prev_token->token_data ? curr->prev_token->token_data : "(null)");
		else
			printf("  Prev token_data: (null)\n");

		if (curr->next_token)
			printf("  Next token_data: %s\n", curr->next_token->token_data ? curr->next_token->token_data : "(null)");
		else
			printf("  Next token_data: (null)\n");

		printf("-----------------------------\n");
		curr = curr->next_token;
	}
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

int	main(int argc, char *argv[])
{
	char	*line;
	t_token	*tokens;

	(void)argv;
	tokens = NULL;
	if (argc > 1)
	{
		printf("This program must be run without any arguments.\n");
		return (EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		tokens = tokenize(line);
		add_history(line);
		if (!syntax_and_heredoc(tokens, &line))
			continue ;
	}
	printf("exit\n");
	return (0);
}
