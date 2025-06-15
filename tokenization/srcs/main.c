/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:25 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/15 14:32:19 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

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

int	main(void)
{
	char	*line;
	t_token	*tokens;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		tokens = tokenize(line);
		if (!tokens)
		{
			fprintf(stderr, "Tokenization failed.\n");
			free(line);
			continue ;
		}
		print_token(tokens);
		while (tokens)
		{
			printf("current %s", tokens->token_data);
			if (tokens->next_token)
				printf("->	next %s\n", tokens->next_token->token_data);
			else
				printf("->	next NULL\n");
			tokens = tokens->next_token;
		}
		free_tokens(tokens);
		free(line);
	}
	printf("exit\n");
	return (0);
}
