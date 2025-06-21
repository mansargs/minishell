/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:25 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/21 13:17:31 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"

static char	*token_type_str(int type)
{
	if (type == TOKEN_WORD)
		return ("WORD");
	if (type == TOKEN_OPERATOR)
		return ("OPERATOR");
	if (type == TOKEN_REDIRECT)
		return ("REDIRECT");
	if (type == TOKEN_META)
		return ("META");
	return ("UNKNOWN");
}

static char	*operator_type_str(int type)
{
	if (type == OPERATOR_PIPE)
		return ("PIPE");
	if (type == OPERATOR_OR)
		return ("OR");
	if (type == OPERATOR_AND)
		return ("AND");
	if (type == OPERATOR_AMP)
		return ("AMP");
	if (type == OPERATOR_DOLLAR)
		return ("DOLLAR");
	if (type == OPERATOR_PAREN_OPEN)
		return ("PAREN_OPEN");
	if (type == OPERATOR_PAREN_CLOSE)
		return ("PAREN_CLOSE");
	return ("NONE");
}

static char	*redirection_type_str(int type)
{
	if (type == REDIRECT_IN)
		return ("IN");
	if (type == REDIRECT_OUT)
		return ("OUT");
	if (type == REDIRECT_APPEND)
		return ("APPEND");
	if (type == REDIRECT_HEREDOC)
		return ("HEREDOC");
	return ("NONE");
}

void	print_token(t_token *token)
{
	while (token)
	{
		printf("Token: %-15s | Type: %-8s", token->token_data,
			token_type_str(token->token_type));
		if (token->token_type == TOKEN_OPERATOR)
			printf(" | Operator: %-11s %d",
				operator_type_str(token->token_operator_type),
				token->token_operator_type);
		else if (token->token_type == TOKEN_REDIRECT)
			printf(" | Redirect: %-11s %d",
				redirection_type_str(token->token_redirect_type),
				token->token_redirect_type);
		else
			printf(" | ------- : ----------- 0");
		printf("\n");
		token = token->next_token;
	}
}

int	main(int argc, char *argv[])
{
	char	*line;
	t_token	*tokens;

	(void)argv;
	if (argc > 1)
	{
		printf("This program must be run without any arguments.\n");
		return (EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("minishell > ");
		if (!line)
			break ;
		if (!*line)
		{
			free(line);
			continue ;
		}
		if (!wait_for_input_if_need(&line))
		{
			if (errno == ENOMEM)
			{
				free(line);
				free_tokens(tokens);
				return (ENOMEM);
			}
			free(line);
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
