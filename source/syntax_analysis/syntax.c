/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:38:09 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/30 16:05:24 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	syntax_and_heredoc(t_token *tokens, char **line)
{
	t_token			*temp;
	unsigned int	i;

	if (strict_syntax_errors(tokens))
		return (free_tokens(tokens), false);
	temp = tokens;
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
		else if (secondary_syntax_errors(temp))
			return (free_tokens(tokens), false);
		temp = temp->next_token;
	}
	if (should_I_wait(tokens->prev_token))
	{
		if (!wait_for_input(temp, line))
			return (false);
		return (syntax_and_heredoc(tokens, line));
	}
	return (true);
}
