/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:28:33 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/06 17:06:18 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static bool	file_in_redirs(t_token *redir, t_shell *shell)
{
	int		fd;
	char	*str;
	int		open_flag;

	open_flag = 0;
	str = open_quotes(shell->envp, redir->file_name,
			&shell->heredoc_quote);
	if (redir->file_name)
		free(redir->file_name);
	redir->file_name = str;
	if (!str)
		return (false);
	fd = open(redir->file_name, O_RDONLY);
	if (fd < 0)
		return (perror(redir->file_name), false);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (true);
}

static bool	file_out_redirs(t_token *redir, t_shell *shell)
{
	int		fd;
	char	*str;
	int		open_flag;

	open_flag = 0;
	if (redir->token_redirect_type == REDIRECT_OUT)
	{
		str = open_quotes(shell->envp, redir->file_name,
				&shell->heredoc_quote);
		if (redir->file_name)
			free(redir->file_name);
		redir->file_name = str;
		if (!str)
			return (false);
		fd = open(redir->file_name, O_WRONLY | O_CREAT
				| O_TRUNC, 0644);
	}
	else
		fd = open(redir->file_name, O_WRONLY | O_CREAT
				| O_APPEND, 0644);
	if (fd < 0)
		return (perror(redir->file_name), false);
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
	}
	if (result)
		return (FUNCTION_SUCCESS);
	return (FUNCTION_FAIL);
}
