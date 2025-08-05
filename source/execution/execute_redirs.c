/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:28:33 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/05 15:00:54 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static bool	file_in_redirs(t_token *redir)
{
	int	fd;

	fd = open(redir->file_name, O_RDONLY);
	if (fd < 0)
		return (perror(redir->file_name), false);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (true);
}

static bool	file_out_redirs(t_token *redir)
{
	int	fd;

	if (redir->token_redirect_type == REDIRECT_OUT)
		fd = open(redir->file_name, O_WRONLY | O_CREAT
				| O_TRUNC, 0644);
	else
		fd = open(redir->file_name, O_WRONLY | O_CREAT
				| O_APPEND, 0644);
	if (fd < 0)
		return (perror(redir->file_name), false);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (true);
}

bool	open_redirects(t_ast *node)
{
	t_token	*redirect;

	if (!node->redir)
		return (true);
	redirect = node->redir;
	while (redirect)
	{
		if (redirect->token_redirect_type == REDIRECT_HEREDOC
			|| redirect->token_redirect_type == REDIRECT_IN)
			file_in_redirs(redirect);
		else
		{
			file_out_redirs(redirect);
		}
		redirect = redirect->next_token;
	}
	return (true);
}
