/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:35:41 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/08 15:44:27 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token_type	get_token_type(const char *token, int len)
{
	if (len == 1)
	{
		if (*token == '|' || *token == '&')
			return (TOKEN_OPERATOR);
		if (*token == '(' || *token == ')')
			return (TOKEN_PAREN);
		if (*token == '<' || *token == '>')
			return (TOKEN_REDIRECT);
	}
	else if (len == 2)
	{
		if (!ft_strncmp(token, "&&", 2) || !ft_strncmp(token, "||", 2))
			return (TOKEN_OPERATOR);
		if (!ft_strncmp(token, ">>", 2) || !ft_strncmp(token, "<<", 2))
			return (TOKEN_REDIRECT);
	}
	return (TOKEN_WORD);
}

static int	handle_operator_token(const char *line, int i, t_token **head)
{
	t_token_type	type;
	t_token			*tok;
	char			*substr;
	int				len;

	len = 1;
	if ((line[i] == '&' && line[i + 1] == '&')
		|| (line[i] == '|' && line[i + 1] == '|')
		|| (line[i] == '<' && line[i + 1] == '<')
		|| (line[i] == '>' && line[i + 1] == '>'))
		len = 2;
	type = get_token_type(&line[i], len);
	substr = ft_substr(&line[i], 0, len);
	if (!substr)
		return (-1);
	tok = create_token(substr, type);
	free(substr);
	if (!tok)
		return (-1);
	add_token(head, tok);
	return (len);
}

static int	handle_word_token(const char *line, int i, t_token **head)
{
	t_token	*tok;
	char	*substr;
	int		len;

	len = get_word_len_with_quotes(&line[i]);
	substr = ft_substr(&line[i], 0, len);
	if (!substr)
		return (-1);
	tok = create_token(substr, TOKEN_WORD);
	free(substr);
	if (!tok)
		return (-1);
	add_token(head, tok);
	return (len);
}

static t_token	*tokenize_loop(char *line, t_token *head)
{
	int	i;
	int	len;

	i = 0;
	while (line[i])
	{
		if (is_space(line[i]))
		{
			++i;
			continue ;
		}
		else if (is_special_char(line[i]))
			len = handle_operator_token(line, i, &head);
		else if (line[i] == '\'' || line[i] == '"')
			len = handle_quots_token(line, i, &head);
		else
			len = handle_word_token(line, i, &head);
		if (len < 0)
			return (free_tokens(head), NULL);
		i += len;
	}
	return (head);
}

t_token	*tokenize(char *line)
{
	t_token	*head;

	head = NULL;
	if (!*line || only_spaces(line))
		return (NULL);
	return (tokenize_loop(line, head));
}
