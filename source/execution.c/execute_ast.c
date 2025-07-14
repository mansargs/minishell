/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:49:43 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/14 16:09:33 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static	void restore_standart_fd(int std_in, int std_out)
{
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	close(std_in);
	close(std_out);
}

bool	open_redirects(t_ast *node)
{
	int		fd;
	t_token	*redirect;

	if (!node->redir)
		return (true);
	redirect = node->redir;
	while (redirect)
	{
		if (redirect->token_redirect_type == REDIRECT_HEREDOC
			|| redirect->token_redirect_type == REDIRECT_IN)
		{
			fd = open(redirect->file_name, O_RDONLY);
			if (fd < 0)
				return (perror(redirect->file_name), false);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else
		{
			if (redirect->token_redirect_type == REDIRECT_OUT)
				fd = open(redirect->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				fd = open(redirect->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				return (perror(redirect->file_name), false);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redirect = redirect->next_token;
	}
	return (true);
}

bool	execute_logic_and(t_ast *node, t_env *env)
{
	if (!execute_ast(node->left_side, env))
		return (false);
	return execute_ast(node->right_side, env);
}

bool	execute_logic_or(t_ast *node, t_env *env)
{
	if (execute_ast(node->left_side, env))
		return (true);
	return execute_ast(node->right_side, env);
}



bool execute_ast(t_ast *node, t_env *env)
{
	int		old_stdin;
	int		old_stdout;
	bool	result;

	if (!node)
		return true;
	old_stdin = dup(STDIN_FILENO);
	old_stdout = dup(STDOUT_FILENO);
	if (!open_redirects(node))
		return (restore_standart_fd(old_stdin, old_stdout), false);
	if (node->cmd->token_operator_type == OPERATOR_AND)
		result = execute_logic_and(node, env);
	else if (node->cmd->token_operator_type == OPERATOR_OR)
		result = execute_ast_or(node, env);
	else if (node->cmd->token_operator_type == OPERATOR_PIPE)
		result = execute_pipe(node, env);
	else if (node->cmd->token_paren_type == PAREN_OPEN)
		result = execute_subshell(node, env);
	else
		result = execute_command(node, env);
	restore_standart_fd(old_stdin, old_stdout);
	return (result);
}



