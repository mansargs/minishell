/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absent_operand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:51:12 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/06 22:26:49 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static bool	read_and_join_line(char **line, char **extra_line)
{
	char	*temp;
	int		len;

	ft_putstr_fd("> ", STDOUT_FILENO);
	*extra_line = get_next_line(STDIN_FILENO);
	if (!*extra_line)
		return (false);
	len = ft_strlen(*extra_line);
	if (only_spaces(*extra_line))
		return (free(*extra_line), read_and_join_line(line, extra_line));
	if (len > 0 && (*extra_line)[len - 1] == '\n')
		(*extra_line)[len - 1] = '\0';
	temp = *line;
	*line = ft_strjoin(*line, *extra_line);
	free(temp);
	if (!*line)
		return (free(*extra_line), false);
	return (true);
}

static bool	validate_and_merge_tokens(t_shell *shell, char *extra_line)
{
	t_token	*new_tokens;
	t_token	*prev;
	t_token	*last;

	new_tokens = tokenize(extra_line);
	free(extra_line);
	if (!new_tokens)
		return (false);
	prev = shell->tokens;
	shell->tokens = new_tokens;
	if (!syntax_and_heredoc(shell))
		return (false);
	last = add_token(&prev, shell->tokens);
	shell->tokens = prev;
	if (last->token_type != TOKEN_OPERATOR)
		return (true);
	return (false);
}

bool	wait_for_input(t_shell *shell, char **line)
{
	char	*extra_line;

	while (1)
	{
		if (!read_and_join_line(line, &extra_line))
			return (false);
		if (validate_and_merge_tokens(shell, extra_line))
			break ;
	}
	return (true);
}

// bool	wait_for_input(t_shell *shell, char **line)
// {
// 	char	*extra_line;
// 	char	*temp_str;
// 	t_token	*new_tokens;
// 	t_token	*prev;
// 	t_token	*last;
// 	int		len;

// 	while (1)
// 	{
// 		ft_putstr_fd("> ", STDOUT_FILENO);
// 		extra_line = get_next_line(STDIN_FILENO);
// 		if (!extra_line)
// 			return (false);
// 		len = ft_strlen(extra_line);
// 		if (only_spaces(extra_line))
// 		{
// 			free(extra_line);
// 			continue;
// 		}
// 		if (len > 0 && extra_line[len - 1] == '\n')
// 			extra_line[len - 1] = '\0';
// 		temp_str = *line;
// 		*line = ft_strjoin(*line, extra_line);
// 		free(temp_str);
// 		if (!*line)
// 			return (free(extra_line), false);
// 		new_tokens = tokenize(extra_line);
// 		free(extra_line);
// 		if (!new_tokens)
// 			return (false);
// 		prev = shell->tokens;
// 		shell->tokens = new_tokens;
// 		if (!syntax_and_heredoc(shell))
// 			return (false);
// 		last = add_token(&prev, shell->tokens);
// 		shell->tokens = prev;
// 		if (last->token_type != TOKEN_OPERATOR)
// 			break ;
// 	}
// 	return (true);
// }
