/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:25 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/09 00:50:13 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

void print_indent(int level)
{
	for (int i = 0; i < level; i++)
		printf("│   ");
}

void print_token_list(t_token *token)
{
	while (token)
	{
		printf("%s ", token->token_data);
		token = token->next_token;
	}
	printf("\n");
}

void print_ast(t_ast *node, int level)
{
	if (!node)
		return;

	print_indent(level);
	printf("● ");
	print_token_list(node->command);

	if (node->left_side)
	{
		print_indent(level + 1);
		printf("├─ Left:\n");
		print_ast(node->left_side, level + 2);
	}

	if (node->right_side)
	{
		print_indent(level + 1);
		printf("└─ Right:\n");
		print_ast(node->right_side, level + 2);
	}
}





int	main(int argc, char *argv[], char **envp)
{
	char	*line;
	t_shell	*shell;
	t_ast	*tree;

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
		if (!(tree = builing_ast(shell->tokens)))
			return (EXIT_FAILURE);
		else
			print_ast(tree, 0);
		free(line);
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
	printf("exit\n");
	return (0);
}
