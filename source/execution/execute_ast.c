/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:49:43 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/06 17:03:48 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	restore_standard_fd(int std_in, int std_out)
{
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	close(std_in);
	close(std_out);
}

int	execute_logic_and(t_ast *node, t_env *env)
{
	int	left_return;

	left_return = execute_ast(node->left_side, env, false);
	if (left_return != FUNCTION_SUCCESS)
		return (left_return);
	return (execute_ast(node->right_side, env, false));
}

int	execute_logic_or(t_ast *node, t_env *env)
{
	int	left_return;

	left_return = execute_ast(node->left_side, env, false);
	if (left_return == FUNCTION_SUCCESS)
		return (left_return);
	return (execute_ast(node->right_side, env, false));
}

int	execute_subshell(t_ast *node, t_env *env, bool has_forked)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (has_forked)
		return (execute_ast(node->left_side, env, true));
	pid = fork();
	if (pid < 0)
		return (perror("fork failed"), FUNCTION_FAIL);
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exit(execute_ast(node->left_side, env, true));
	}
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waiting failed");
		env->shell->exit_code = 1;
	}
	else
		handle_child_status(status, env);
	return (env->shell->exit_code);
}

int	execute_ast(t_ast *node, t_env *env, bool has_forked)
{
	int	old_stdin;
	int	old_stdout;
	int	result;

	if (!node)
		return (0);
	old_stdin = dup(STDIN_FILENO);
	old_stdout = dup(STDOUT_FILENO);
	result = 0;
	if (open_redirects(node, env->shell) == FUNCTION_FAIL)
		return (restore_standard_fd(old_stdin, old_stdout), FUNCTION_FAIL);
	if (node->cmd && node->cmd->token_operator_type == OPERATOR_AND)
		result = execute_logic_and(node, env);
	else if (node->cmd && node->cmd->token_operator_type == OPERATOR_OR)
		result = execute_logic_or(node, env);
	else if (node->cmd && node->cmd->token_operator_type == OPERATOR_PIPE)
		result = execute_pipe(node, env);
	else if (node->cmd && node->cmd->token_paren_type == PAREN_OPEN)
		result = execute_subshell(node, env, has_forked);
	else if (node->cmd)
		result = execute_command(node, env, has_forked);
	restore_standard_fd(old_stdin, old_stdout);
	return (result);
}
