/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:28:33 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/09 23:31:22 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	open_redirs_quote(t_token *redir, t_shell *shell)
{
	char	*str;

	str = open_quotes(shell->my_env, shell->envp, redir->file_name,
			&shell->heredoc_quote);
	if (redir->file_name)
		free(redir->file_name);
	redir->file_name = str;
	if (!str)
		return ;
}

static bool	file_in_redirs(t_token *redir, t_shell *shell)
{
	int		fd;

	open_redirs_quote(redir, shell);
	fd = open(redir->file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		return (perror(redir->file_name), false);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (true);
}

static bool	file_out_redirs(t_token *redir, t_shell *shell)
{
	int		fd;

	if (redir->token_redirect_type == REDIRECT_OUT)
	{
		open_redirs_quote(redir, shell);
		fd = open(redir->file_name, O_WRONLY | O_CREAT
				| O_TRUNC, 0644);
	}
	else
	{
		open_redirs_quote(redir, shell);
		fd = open(redir->file_name, O_WRONLY | O_CREAT
				| O_APPEND, 0644);
	}
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		return (perror(redir->file_name), false);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (true);
}

int	open_redirects(t_ast *node, t_shell *shell)
{
	t_token	*redirect;
	bool	result;

	if (!node->redir)
		return (FUNCTION_SUCCESS);
	redirect = node->redir;
	while (redirect)
	{
		if (redirect->token_redirect_type == REDIRECT_HEREDOC
			|| redirect->token_redirect_type == REDIRECT_IN)
			result = file_in_redirs(redirect, shell);
		else
			result = file_out_redirs(redirect, shell);
		redirect = redirect->next_token;
		if (!result)
			return (FUNCTION_FAIL);
	}
	return (FUNCTION_SUCCESS);
}
