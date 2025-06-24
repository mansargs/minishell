/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:25 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/25 02:49:26 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static char	*token_type_str(int type)
{
	if (type == TOKEN_WORD)
		return ("WORD");
	if (type == TOKEN_OPERATOR)
		return ("OPERATOR");
	if (type == TOKEN_REDIRECT)
		return ("REDIRECT");
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
		line = readline("minishell > ");
		if (!line)
			break ;
		tokens = tokenize(line);
		heredoc(tokens);
		// if (!tokens || syntax_analysis(tokens))
		// {
		// 	add_history(line);
		// 	free(line);
		// 	continue ;
		// }
		// if (wait_for_input_if_need(tokens, line))
		// {
		// 	if (errno == ENOMEM)
		// 		return (free_tokens(tokens), ENOMEM);
		// 	continue ;
		// }
		// add_history(line);
		// tokens = tokenize(line);
		// if (!tokens)
		// {
		// 	printf("Tokenization failed.\n");
		// 	free(line);
		// 	continue ;
		// }
		// print_token(tokens);
		// if (syntax_analysis(tokens))
		// {
		// 	free_tokens(tokens);
		// 	free(line);
		// 	continue ;
		// }
		// free_tokens(tokens);
		// free(line);
	}
	printf("exit\n");
	return (0);
}
