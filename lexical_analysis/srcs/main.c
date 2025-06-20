/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:25 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/20 14:30:22 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	print_token(t_token *token)
{
	while (token)
	{
		printf("Token: %-15s | Type: %-2d | Class: %-2d\n",
			token->token_data,
			token->token_type,
			token->token_class);
		token = token->next_token;
	}
}

int	main(int argc, char *argv[])
{
	char	*line;
	t_token	*tokens;

	(void) argv;
	if (argc > 1)
		return (printf("This program must be run without any arguments.\n"), EXIT_FAILURE);
	line = NULL;
	tokens = NULL;
	while (1)
	{
		line = readline("minishell > ");
		if (!line)
			break ;
		if (!*line)
			continue ;
		if (!wait_for_input_if_need(&line))
		{
			if (errno == ENOMEM)
				return (free(line), free_tokens(tokens), ENOMEM);
			continue ;
		}
		add_history(line);
		tokens = tokenize(line);
		if (!tokens)
		{
			printf("Tokenization failed.\n");
			free(line);
			continue ;
		}
		print_token(tokens);
		free_tokens(tokens);
		free(line);
	}
	printf("exit\n");
	return (0);
}
