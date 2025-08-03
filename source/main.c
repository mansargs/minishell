/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:25 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/03 20:19:14 by alisharu         ###   ########.fr       */
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

void	conditional_free(t_shell **shell, bool ast, bool minishell)
{
	if (ast == true)
		free_ast(&(*shell)->tree);
	if (minishell == true)
		free_shell(shell);
}

void	ps_path(t_shell *shell)
{
	char	*user_name;
	char	*pwd_path;
	char	*result_line;

	user_name = get_env_value(shell->envp, "USER");
	if (!user_name)
		user_name = ft_strdup("unknown");
	printf("%s\n", user_name);
	pwd_path = shell->pwd;
	result_line = ft_strjoin("minishell@", user_name);
	result_line = ft_strjoin(result_line, ":");
	result_line = ft_strjoin(result_line, pwd_path);
	result_line = ft_strjoin(result_line, "$ ");
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
		// user_name = get_env_value(shell->envp, "USER");
		// if (!user_name)
		// 	user_name = ft_strdup("unknown");
		// printf("%s\n", user_name);
		// pwd_path = shell->pwd;
		// result_line = ft_strjoin("minishell@", user_name);
		// result_line = ft_strjoin(result_line, ":");
		// result_line = ft_strjoin(result_line, pwd_path);
		// result_line = ft_strjoin(result_line, "$ ");
		setup_signals();
		line = readline("minishell$ ");
		if (!line)
			break ;
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
				continue ;
			}
			else
				return (free(line), free_tokens(&shell->tokens), free_shell(&shell), ENOMEM);
		}
		add_history(line);
		if (shell->tokens && !valid_line(shell, &line))
		{
			free_tokens(&shell->tokens);
			free(line);
			continue ;
		}
		free(line);
		shell->tree = building_ast(shell->tokens);
		if (!shell->tree)
			return (free_shell(&shell), ENOMEM);
		// print_ast_full(shell->tree, 0);
		execute_ast(shell->tree, shell->my_env, false);
		conditional_free(&shell, true, false);
		// free(result_line);
		// free_ast(&shell->tree);
		// free_tokens(&shell->tokens);
		// free(line);
	}
	conditional_free(&shell, true, true);
	printf("exit\n");
	return (0);
}
