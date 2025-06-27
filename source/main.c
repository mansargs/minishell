/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:25 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/27 17:04:59 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

// static char	*token_type_str(int type)
// {
// 	if (type == TOKEN_WORD)
// 		return ("WORD");
// 	if (type == TOKEN_OPERATOR)
// 		return ("OPERATOR");
// 	if (type == TOKEN_REDIRECT)
// 		return ("REDIRECT");
// 	return ("UNKNOWN");
// }

// static char	*operator_type_str(int type)
// {
// 	if (type == OPERATOR_PIPE)
// 		return ("PIPE");
// 	if (type == OPERATOR_OR)
// 		return ("OR");
// 	if (type == OPERATOR_AND)
// 		return ("AND");
// 	if (type == OPERATOR_AMP)
// 		return ("AMP");
// 	if (type == OPERATOR_PAREN_OPEN)
// 		return ("PAREN_OPEN");
// 	if (type == OPERATOR_PAREN_CLOSE)
// 		return ("PAREN_CLOSE");
// 	return ("NONE");
// }

// static char	*redirection_type_str(int type)
// {
// 	if (type == REDIRECT_IN)
// 		return ("IN");
// 	if (type == REDIRECT_OUT)
// 		return ("OUT");
// 	if (type == REDIRECT_APPEND)
// 		return ("APPEND");
// 	if (type == REDIRECT_HEREDOC)
// 		return ("HEREDOC");
// 	return ("NONE");
// }

void print_tokens_with_neighbors(t_token *head)
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

bool	syntax_error_before_heredoc(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	if (temp && temp->token_type == TOKEN_OPERATOR &&
		temp->token_operator_type != OPERATOR_PAREN_OPEN)
		return (printf("%s `%s'\n", SYN_ERR, temp->token_data), true);
	while (temp)
	{
		if (temp->token_type == TOKEN_REDIRECT &&
			temp->next_token && temp->next_token->token_type != TOKEN_WORD)
			return (printf("%s `%s'\n", SYN_ERR, temp->next_token->token_data), true);
		if ((temp->token_operator_type == OPERATOR_AND || temp->token_operator_type == OPERATOR_OR) &&
			temp->next_token &&
			(temp->next_token->token_operator_type == OPERATOR_AND || temp->next_token->token_operator_type == OPERATOR_OR))
			return (printf("%s `%s'\n", SYN_ERR, temp->next_token->token_data), true);
		temp = temp->next_token;
	}
	return (false);
}


bool	syntax_and_heredoc(t_token *tokens, char **line)
{
	t_token			*temp;
	unsigned int	i;

	if (syntax_error_before_heredoc(tokens))
		return (false);
	temp = tokens;
	while (temp)
	{
		++i;
		if (temp->token_redirect_type == REDIRECT_HEREDOC)
		{
			if (!temp->file_name)
				temp->file_name = open_heredoc(temp, &i);
			if (!temp->file_name)
				return (false);
		}
		if (syntax_analysis(temp))
			return (free_tokens(tokens), false);
		if (!temp->next_token && should_I_wait(temp))
		{
			if (!wait_for_input(temp, line))
				return (false);
			return syntax_and_heredoc(tokens, line);
		}
		temp = temp->next_token;
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
		// print_tokens_with_neighbors(tokens);
		if (!syntax_and_heredoc(tokens, &line))
		{
			if (errno)
				break;
		}
		continue;
	}
	printf("exit\n");
	return (0);
}
