/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:38:09 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/01 13:31:23 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	syntax_and_heredoc(t_token *tokens, char **line)
{
	t_token			*temp;
	int				opened_parenthesis;
	unsigned int	i;

	if (strict_syntax_errors(tokens))
		return (free_tokens(tokens), false);
	temp = tokens;
	opened_parenthesis = 0;
	while (temp)
	{
		++i;
		if (temp->token_redirect_type == REDIRECT_HEREDOC)
		{
			if (!temp->file_name)
				temp->file_name = open_heredoc(temp, &i);
			if (!temp->file_name)
				return (false);
		}
		else if (secondary_syntax_errors(temp, &opened_parenthesis))
			return (free_tokens(tokens), false);
		if (!temp->next_token && should_I_wait(temp))
		{
			if (!wait_for_input(temp, line))
				return (false);
			return (syntax_and_heredoc(tokens, line));
		}
		temp = temp->next_token;
	}
	return (true);
}
