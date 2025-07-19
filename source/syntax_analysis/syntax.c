/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:38:09 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/20 02:06:03 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	is_there_heredoc(t_token *token, bool *heredoc_flag)
{
	const t_token	*temp;

	temp = token;
	while (temp)
	{
		if (temp->token_redirect_type == REDIRECT_HEREDOC)
		{
			*heredoc_flag = true;
			return (true);
		}
		temp = temp->next_token;
	}
	return (false);
}

bool	syntax_and_heredoc(t_shell *shell)
{
	t_token	*temp;
	int		opened_parenthesis;

	if (strict_syntax_errors(shell))
		return (free_tokens(shell->tokens), false);
	temp = shell->tokens;
	opened_parenthesis = 0;
	while (temp)
	{
		if (temp->token_redirect_type == REDIRECT_HEREDOC)
		{
			if (!temp->file_name)
				temp->file_name = open_heredoc(temp, shell->history.fd);
			if (!temp->file_name)
				return (false);
		}
		else if (secondary_syntax_errors(temp, &opened_parenthesis))
			return (free_tokens(shell->tokens), false);
		temp = temp->next_token;
	}
	return (true);
}

bool	valid_line(t_shell *shell, char **line)
{
	t_token	*last;

	if (is_there_heredoc(shell->tokens, &shell->history.is_there_heredoc))
	{
		ft_putendl_fd(*line, shell->history.fd);
		free(*line);
		*line = NULL;
	}
	if (!syntax_and_heredoc(shell))
		return (false);
	last = last_token(shell->tokens);
	if (last && last->token_type == TOKEN_OPERATOR)
		if (!wait_for_input(shell, line))
			return (free(*line), *line = NULL, false);
	ft_putendl_fd(*line, shell->history.fd);
	return (true);
}
