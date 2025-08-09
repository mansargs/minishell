/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:38:09 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/09 19:46:24 by mansargs         ###   ########.fr       */
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
	char	*heredoc_file;

	if (strict_syntax_errors(shell))
		return (free_tokens(&shell->tokens), false);
	temp = shell->tokens;
	opened_parenthesis = 0;
	while (temp)
	{
		if (temp->token_redirect_type == REDIRECT_HEREDOC)
		{
			if (!temp->file_name)
			{
				heredoc_file = open_heredoc(shell, temp, shell->history.fd);
				if (!heredoc_file)
					return (false);
				temp->file_name = heredoc_file;
			}
		}
		else if (secondary_syntax_errors(temp, &opened_parenthesis))
			return (free_tokens(&shell->tokens), false);
		temp = temp->next_token;
	}
	return (true);
}

static void	handle_heredoc_flag(t_shell *shell, char **line)
{
	if (!is_there_heredoc(shell->tokens, &shell->history.is_there_heredoc))
		return ;
	ft_putendl_fd(*line, shell->history.fd);
	free(*line);
	*line = NULL;
}

bool	valid_line(t_shell *shell, char **line)
{
	handle_exitstatus(shell);
	handle_heredoc_flag(shell, line);
	if (!syntax_and_heredoc(shell))
	{
		shell->my_env->exit_code = 2;
		return (false);
	}
	if (*line)
		ft_putendl_fd(*line, shell->history.fd);
	return (true);
}

int	check_is_open_quote(int quote)
{
	if (quote)
		return (print_error("newline"), 0);
	return (1);
}
