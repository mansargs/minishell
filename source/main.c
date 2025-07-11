/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:25 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/11 13:58:28 by alisharu         ###   ########.fr       */
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

void print_token_list(t_token *token)
{
	while (token)
	{
		printf("%s ", token->token_data);
		token = token->next_token;
	}
	printf("\n");
}

// void print_ast(t_ast *node, int level)
// {
// 	if (!node)
// 		return;

// 	print_indent(level);
// 	printf("● ");
// 	print_token_list(node->command);

// 	t_redirection *redir = node->redirect;
// 	while (redir)
// 	{
// 		print_indent(level + 1);
// 		printf("↳ Redirect: %s\n", redir->token->token_data);
// 		print_indent(level + 1);
// 		printf("↳ Target:   %s\n", redir->filename);
// 		redir = redir->next;
// 	}

// 	if (node->left_side)
// 	{
// 		print_indent(level + 1);
// 		printf("├─ Left:\n");
// 		print_ast(node->left_side, level + 2);
// 	}

// 	if (node->right_side)
// 	{
// 		print_indent(level + 1);
// 		printf("└─ Right:\n");
// 		print_ast(node->right_side, level + 2);
// 	}
// }

////

void	print_env_table(t_env *env)
{
	int				i;
	t_env_node		*node;

	i = 0;
	while (i < HASH_SIZE)
	{
		node = env->env[i];
		// if (node)
		// 	printf("Index %d:\n", i);
		while (node)
		{
			printf("  \033[34m%s\033[0m", node->key);
			if (node->is_equal)
			{
				printf("\033[37m=\033[0m");
				if (node->value)
					printf("\033[32m%s\033[0m", node->value);
			}
			printf("\n");
			node = node->next;
		}
		i++;
	}
}


int	main(int argc, char *argv[], char **envp)
{
	char	*line;
	t_shell	*shell;
	t_env	*my_env;

	(void)argv;
	if (argc > 1)
	{
		printf("This program must be run without any arguments.\n");
		return (EXIT_FAILURE);
	}
	shell = init_shell(envp);
	my_env = init_env(envp);
	if (!my_env)
	{
		printf("Failed to initialize env table.\n");
		return (1);
	}

	printf("=== Environment Table ===\n\n\n\n\n");
	print_env_table(my_env);
	printf("=========================\n");
	env_set(my_env, "HELLO", "WORLD", 1);
	env_set(my_env, "USER", "zasdfghj", 1);
	env_set(my_env, "PATH", "/usr/pxik", 1);
	env_set(my_env, "ALICEEEE", "", 1);
	printf("=== After Manual Additions ===\n\n\n\n\n");

	print_env_table(my_env);
	printf("==============================\n");
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
		handle_builtin_commands(shell, my_env);
		free(line);
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
	free_env_table(my_env);
	if (shell)
		free(shell);
	shell = NULL;
	printf("exit\n");
	return (0);
}
