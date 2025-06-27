/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absent_operand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:51:12 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/27 16:57:17 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	should_I_wait(const t_token *last_token)
{
	if (last_token->token_type == TOKEN_OPERATOR && last_token->token_operator_type != OPERATOR_PAREN_CLOSE)
		return (true);
	return (false);
}

bool	wait_for_input(t_token *last, char **line)
{
	char	*extra_line;
	char	*temp_str;
	t_token	*new_tokens;
	int		len;

	ft_putstr_fd("> ", STDOUT_FILENO);
	extra_line = get_next_line(STDIN_FILENO);
	if (!extra_line)
		return (false);
	len = ft_strlen(extra_line);
	if (len > 0 && extra_line[len - 1] == '\n')
		extra_line[len - 1] = '\0';
	temp_str = *line;
	*line = ft_strjoin(*line, extra_line);
	free(temp_str);
	if (!*line)
		return (false);
	new_tokens = tokenize(extra_line);
	free(extra_line);
	add_token(&last, new_tokens);
	return (true);
}
