/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absent_operand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:51:12 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/03 16:53:15 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	wait_for_input(t_token *last, char **line)
{
	char	*extra_line;
	char	*temp_str;
	t_token	*new_tokens;
	int		len;

	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		extra_line = get_next_line(STDIN_FILENO);
		if (!extra_line)
			return (false);
		len = ft_strlen(extra_line);
		if (only_spaces(extra_line))
		{
			free(extra_line);
			continue;
		}
		if (len > 0 && extra_line[len - 1] == '\n')
			extra_line[len - 1] = '\0';
		temp_str = *line;
		*line = ft_strjoin(*line, extra_line);
		free(temp_str);
		if (!*line)
			return (free(extra_line), false);
		new_tokens = tokenize(extra_line);
		free(extra_line);
		if (!new_tokens)
			return (false);
		if (!syntax_and_heredoc(new_tokens))
			return (false);
		last = add_token(&last, new_tokens);
		if (last->token_type != TOKEN_OPERATOR)
			break ;
	}
	return (true);
}
