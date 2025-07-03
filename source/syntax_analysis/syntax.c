/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:38:09 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/03 16:11:39 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	syntax_and_heredoc(t_token *tokens)
{
	t_token	*temp;
	int		opened_parenthesis;

	if (strict_syntax_errors(tokens))
		return (free_tokens(tokens), false);
	temp = tokens;
	opened_parenthesis = 0;
	while (temp)
	{
		if (temp->token_redirect_type == REDIRECT_HEREDOC)
		{
			if (!temp->file_name)
				temp->file_name = open_heredoc(temp);
			if (!temp->file_name)
				return (false);
		}
		else if (secondary_syntax_errors(temp, &opened_parenthesis))
			return (free_tokens(tokens), false);
		temp = temp->next_token;
	}
	return (true);
}

bool	valid_line(t_token *tokens, char **line)
{
	t_token	*last;

	if (!syntax_and_heredoc(tokens))
		return (false);
	last = last_token(tokens);
	if (last->token_type == TOKEN_OPERATOR)
		if (!wait_for_input(last, line))
			return (false);
	return (true);
}
