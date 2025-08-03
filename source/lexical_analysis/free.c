/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 02:22:30 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/04 02:32:12 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	free_matrix(char ***matrix)
{
	int	i;

	if (!matrix || !*matrix)
		return ;
	i = 0;
	while ((*matrix)[i])
	{
		free((*matrix)[i]);
		i++;
	}
	free(*matrix);
	*matrix = NULL;
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
