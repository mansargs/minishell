/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defective_operator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:51:12 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/25 17:27:46 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static t_token	*find_last_token(const t_token *tokens)
{
	t_token	*last_token;

	last_token = tokens;
	if (!last_token)
		return (NULL);
	while (last_token->next_token)
		last_token = last_token->next_token;
	return (last_token);
}

static bool	should_I_wait(const t_token *last_token)
{
	int	len;

	len = ft_strlen(last_token->token_data);
	if ((len >= 2 && (!ft_strncmp(last_token->token_data, "||", 2)
				|| !ft_strncmp(last_token->token_data, "&&", 2)))
		|| (len >= 1 && !ft_strncmp(last_token->token_data, "|", 1)))
		return (true);
	return (false);
}

bool	wait_for_input_if_need(t_token **head, char *line)
{
	t_token	*last_token;
	t_token	*new_tokens;
	int		len;
	char	*extra_line;
	char	*temp;

	while (1)
	{
		last_token = find_last_word(&head);
		if (!should_I_wait(last_token))
			break ;
		printf(" > \n");
		extra_line = get_next_line(STDIN_FILENO);
		if (!extra_line)
			return (false);
		len = ft_strlen(extra_line);
		if (extra_line[len - 1] == '\n')
			extra_line[len - 1] = '\0';
		new_tokens = tokenize(extra_line);
		if ()
		temp = *line;
		*line = ft_strjoin(*line, extra_line);
		free(extra_line);
		free(temp);
		if (!*line)
			return (false);
	}
	return (free( true);
}
