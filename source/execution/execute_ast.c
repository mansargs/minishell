/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:49:43 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/10 00:16:54 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	restore_standard_fd(int std_in, int std_out)
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
	int		old_stdin_stdout[2];

	status = 0;
	old_stdin_stdout[0] = dup(STDIN_FILENO);
	old_stdin_stdout[1] = dup(STDOUT_FILENO);
	if (has_forked)
	{
		if (open_redirects(node, env->shell) == FUNCTION_FAIL)
			return (restore_standard_fd(old_stdin_stdout[0],
					old_stdin_stdout[1]), FUNCTION_FAIL);
		return (execute_ast(node->left_side, env, true));
	}
	pid = fork();
	if (pid < 0)
		return (perror("fork failed"), FUNCTION_FAIL);
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (open_redirects(node, env->shell) == FUNCTION_FAIL)
			exit(1);
		exit(execute_ast(node->left_side, env, true));
	}
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waiting failed");
		env->exit_code = 1;
	}
	else
		handle_child_status(status, env);
	restore_standard_fd(old_stdin_stdout[0], old_stdin_stdout[1]);
	return (env->exit_code);
}

int	execute_ast(t_ast *node, t_env *env, bool has_forked)
{
	int	result;

	if (!node)
		return (0);
	result = 0;
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
	return (result);
}
