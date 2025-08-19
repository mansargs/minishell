/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:49:43 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/19 19:17:39 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	restore_standard_fd(t_env *env)
{
	if (env->old_stdin != -1)
	{
		dup2(env->old_stdin, STDIN_FILENO);
		close(env->old_stdin);
		env->old_stdin = -1;
	}
	if (env->old_stdout != -1)
	{
		dup2(env->old_stdout, STDOUT_FILENO);
		close(env->old_stdout);
		env->old_stdout = -1;
	}
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
	if (env->exit_code == 130 || env->exit_code == 131)
		return (env->exit_code);
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
		default_signals_setup();
		status = execute_ast(node->left_side, env, true);
		free_all_data(env->shell, NULL, false);
		exit(status);
	}
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waiting failed");
		env->exit_code = 1;
	}
	else
		handle_child_status(status, env);
	return (env->exit_code);
}

int	execute_ast(t_ast *node, t_env *env, bool has_forked)
{
	int	result;

	if (!node)
		return (FUNCTION_SUCCESS);
	if (if_are_redir_open(node, env) == FUNCTION_FAIL)
		return (FUNCTION_FAIL);
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
	if (env->old_stdin != -1 || env->old_stdout != -1)
		restore_standard_fd(env);
	return (result);
}
