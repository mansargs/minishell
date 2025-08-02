/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:25 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/02 22:00:55 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

volatile sig_atomic_t	g_received_signal;

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
			if (node->has_equal_sign)
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

// void	print_list(t_shell *shell)
// {
// 	t_token	*tmp;

// 	tmp = shell->tokens;
// 	while (tmp != NULL)
// 	{
// 		printf("%s -> ", tmp->token_data);
// 		tmp = tmp -> next_token;
// 	}
// 	printf("NULL\n");
// }

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

void	free_shell(t_shell **shell)
{
	if (!*shell)
		return ;
	free((*shell)->pwd);
	if ((*shell)->history.fd >= 0)
		close((*shell)->history.fd);
	if ((*shell)->my_env)
		free_env_table((*shell)->my_env);
	free(*shell);
	*shell = NULL;
}


static void print_indent(int level)
{
	for (int i = 0; i < level; ++i)
		printf("│   ");
}

static void print_token_chain(t_token *tok)
{
	while (tok)
	{
		printf("%s", tok->token_data);
        if (tok->file_name)
            printf("%s", tok->file_name);
		if (tok->next_token)
			printf(" ");
		tok = tok->next_token;
	}
}

static void print_redir_chain(t_token *redir)
{
	if (!redir)
		return;
	printf(" [ ");
	print_token_chain(redir);
	printf(" ]");
}

void print_ast_full(t_ast *node, int level)
{
	print_indent(level);
	if (node->cmd && node->cmd->token_paren_type == PAREN_OPEN)
	{
		// Subshell detected
		printf("● Subshell: ( ) ");
		print_redir_chain(node->redir);
		printf("\n");

		print_indent(level + 1);
		printf("└─ Subshell Body:\n");
		print_ast_full(node->left_side, level + 2);

		// ❌ DO NOT print left_side and right_side again
		return;
	}

	if (node->cmd && node->cmd->token_type == TOKEN_OPERATOR)
	{
		printf("● Operator: %s ", node->cmd->token_data);
	}
	else
	{
		printf("● Command: ");
		print_token_chain(node->cmd);
		print_redir_chain(node->redir);
	}
	printf("\n");

	if (node->left_side)
	{
		print_indent(level + 1);
		printf("├─ Left:\n");
		print_ast_full(node->left_side, level + 2);
	}
	if (node->right_side)
	{
		print_indent(level + 1);
		printf("└─ Right:\n");
		print_ast_full(node->right_side, level + 2);
	}
}

void conditional_free(t_shell **shell, bool ast, bool minishell)
{
	if (ast == true)
		free_ast(&(*shell)->tree);
	if (minishell == true)
		free_shell(shell);
}
int	main(int argc, char *argv[], char **envp)
{
	char	*line;
	t_shell	*shell;


	(void) argv;
	if (argc > 1)
		return (printf("This program must be run without any arguments.\n"),
			EXIT_FAILURE);
	shell = init_shell(envp);
	if (!shell)
		return (ENOMEM);
	if (!init_env(shell, envp))
		return (printf("Failed to initialize env table.\n"),
			free_tokens(&shell->tokens),
			free_shell(&shell), ENOMEM);
	while (1)
	{
		setup_signals();
		line = readline("minishell$ ");
		if (!line)
			break;
		if (g_received_signal)
		{
			shell->exit_code = g_received_signal + 128;
			g_received_signal = 0;
		}
		shell->tokens = tokenize(line, &shell->mem_error);
		if (!shell->tokens)
		{
			if (shell->mem_error == false)
			{
				free(line);
				continue;
			}
			else
				return (free(line), free_tokens(&shell->tokens), free_shell(&shell), ENOMEM);
		}
		add_history(line);
		if (shell->tokens && !valid_line(shell, &line))
		{
			free_tokens(&shell->tokens);
			free(line);
			continue;
		}
		free(line);
		shell->tree = building_ast(shell->tokens);
		if (!shell->tree)
			return (free_shell(&shell), ENOMEM);
		// print_ast_full(shell->tree, 0);
		execute_ast(shell->tree, shell->my_env, false);
		conditional_free(&shell, true, false);
		// free_ast(&shell->tree);
		// free_tokens(&shell->tokens);
		// free(line);
	}
	conditional_free(&shell, true, true);
	printf("exit\n");
	return (0);
}
