/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:25 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/14 23:44:16 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	word_len(const char *line)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (line[i])
	{
		if (!single_quotes && !double_quotes && is_space(line[i]))
			break ;
		if (!single_quotes && !double_quotes && is_special_char(line[i]))
			break ;
		if (line[i] == '\'' && !double_quotes)
			single_quotes = !single_quotes;
		else if (line[i] == '"' && !single_quotes)
			double_quotes = !double_quotes;
		i++;
	}
	return (i);
}

t_token	*create_token(const char *t_data,
		t_token_class t_class, t_token_type t_type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->token_data = ft_strdup(t_data);
	token->token_class = t_class;
	token->token_type = t_type;
	token->next_token = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*tmp;

	if (!head || !new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	tmp = *head;
	while (tmp->next_token)
		tmp = tmp->next_token;
	tmp->next_token = new_token;
}


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

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next_token;
		free(tmp->token_data);
		free(tmp);
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
				printf("   next %s\n", tokens->next_token->token_data);
			else
				printf("   next NULL\n");
			tokens = tokens->next_token;
		}
		free_tokens(tokens);
		free(line);
	}
	printf("exit\n");
	return (0);
}
