/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_free_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 02:53:04 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/14 16:21:16 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_all_data(t_shell *shell, char **argv)
{
	if (shell->my_env->old_stdin != STDIN_FILENO)
		close(shell->my_env->old_stdin);
	if (shell->my_env->old_stdout != STDOUT_FILENO)
		close(shell->my_env->old_stdout);
	close(shell->history.fd);
	if (argv)
		free_matrix(&argv);
	free_env_table(shell->my_env);
	shell->my_env = NULL;
	// if (shell->tokens)
	// 	free_tokens(&shell->tokens);
	conditional_free(&shell, true, true);
}

void	free_ast(t_ast **tree)
{
	if (!tree || !*tree)
		return ;
	if ((*tree)->left_side)
		free_ast(&(*tree)->left_side);
	if ((*tree)->right_side)
		free_ast(&(*tree)->right_side);
	if ((*tree)->cmd)
		free_tokens(&(*tree)->cmd);
	if ((*tree)->redir)
		free_tokens(&(*tree)->redir);
	free(*tree);
	*tree = NULL;
}

void	free_env_table(t_env *env)
{
	t_env_node	*current;
	t_env_node	*next;
	int			i;

	i = 0;
	while (i < HASH_SIZE)
	{
		current = env->env[i];
		while (current)
		{
			next = current->next;
			free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			current = next;
		}
		i++;
	}
	free(env);
}

void	free_shell(t_shell **shell)
{
	if (!*shell)
		return ;
	free((*shell)->pwd);
	free((*shell)->username);
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
