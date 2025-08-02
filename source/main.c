/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:25 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/02 17:21:55 by mansargs         ###   ########.fr       */
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
	if ((*shell)->tokens)
		free_tokens(&(*shell)->tokens);
	if ((*shell)->history.fd >= 0)
		close((*shell)->history.fd);
	if ((*shell)->tree)
		free_ast(&(*shell)->tree);
	if ((*shell)->my_env)
		free_env_table((*shell)->my_env);
	free(*shell);
	*shell = NULL;
}



static const char *get_token_type_str(t_token_type type)
{
	if (type == TOKEN_WORD) return "WORD";
	if (type == TOKEN_OPERATOR) return "OPERATOR";
	if (type == TOKEN_PAREN) return "PAREN";
	if (type == TOKEN_REDIRECT) return "REDIRECT";
	return "UNKNOWN";
}

static const char *get_operator_type_str(t_operator_type type)
{
	if (type == OPERATOR_PIPE) return "PIPE";
	if (type == OPERATOR_OR) return "OR";
	if (type == OPERATOR_AND) return "AND";
	return "NONE";
}

static const char *get_redirection_type_str(t_redirection_type type)
{
	if (type == REDIRECT_IN) return "IN";
	if (type == REDIRECT_OUT) return "OUT";
	if (type == REDIRECT_APPEND) return "APPEND";
	if (type == REDIRECT_HEREDOC) return "HEREDOC";
	return "NONE";
}

static const char *get_paren_type_str(t_paren_type type)
{
	if (type == PAREN_OPEN) return "OPEN";
	if (type == PAREN_CLOSE) return "CLOSE";
	return "NONE";
}

void print_tokens(t_token *head)
{
	t_token *current = head;
	int i = 0;

	while (current)
	{
		printf("Token %d:\n", i++);
		printf("  Data:           %s\n", current->token_data ? current->token_data : "(null)");
		printf("  File name:      %s\n", current->file_name ? current->file_name : "(null)");
		printf("  Type:           %s\n", get_token_type_str(current->token_type));
		printf("  Operator type:  %s\n", get_operator_type_str(current->token_operator_type));
		printf("  Redirect type:  %s\n", get_redirection_type_str(current->token_redirect_type));
		printf("  Paren type:     %s\n", get_paren_type_str(current->token_paren_type));
		printf("  Prev:           %p\n", (void *)current->prev_token);
		printf("  Next:           %p\n", (void *)current->next_token);
		printf("--------------------------------------------------\n");
		current = current->next_token;
	}
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
				return (free(line), free_shell(&shell), ENOMEM);
		}
		add_history(line);
		if (shell->tokens && !valid_line(shell, &line))
		{
			free_tokens(&shell->tokens);
			free(line);
			continue;
		}
		free_tokens(&shell->tokens);
		free(line);
		// if (!(shell->tree = building_ast(shell->tokens)))
		// {
		// 	free_tokens(&shell->tokens);
		// 	return (EXIT_FAILURE);
		// }
		// execute_ast(shell->tree, shell->my_env, 0);

		// free_ast(&shell->tree);
		// free_tokens(&shell->tokens);
		// free(line);
	}
	free_shell(&shell);

	printf("exit\n");
	return (0);
}
