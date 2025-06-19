/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:35:41 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/19 15:56:52 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"

t_token	*create_token(const char *t_data,
		t_token_class t_class, t_token_type t_type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->token_data = ft_strdup(t_data);
	token->token_class = t_class;
	token->token_type = t_type;
	token->next_token = NULL;
	return (token);
}

static int	word_len(const char *line)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (line[i])
	{
		if (!single_quotes && !double_quotes && is_space(line[i]))
			break ;
		if (!single_quotes && !double_quotes && is_special_char(line[i]))
			break ;
		if (line[i] == '\'' && !double_quotes)
			single_quotes = !single_quotes;
		else if (line[i] == '"' && !single_quotes)
			double_quotes = !double_quotes;
		if (line[i] == '$' && !single_quotes)
		{
			i++;
			while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
				i++;
			continue ;
		}
		i++;
	}
	return (i);
}

static int	handle_special_token(const char *line, int i, t_token **head)
{
	t_token_class	class;
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
	class = get_token_class(line[i]);
	type = get_token_type(&line[i], len);
	substr = ft_substr(&line[i], 0, len);
	if (!substr)
		return (-1);
	tok = create_token(substr, class, type);
	free(substr);
	if (!tok)
		return (-1);
	add_token(head, tok);
	return (len);
}

static int	handle_word_token(const char *line, int i, t_token **head)
{
	t_token			*tok;
	char			*substr;
	int				len;

	len = word_len(&line[i]);
	substr = ft_substr(&line[i], 0, len);
	if (!substr)
		return (-1);
	tok = create_token(substr, TOKEN_CLASS_WORD, TOKEN_WORD);
	free(substr);
	if (!tok)
		return (-1);
	add_token(head, tok);
	return (len);
}

t_token	*tokenize(char *line)
{
	t_token	*head;
	int		len;
	int		i;

	i = 0;
	head = NULL;
	while (line[i])
	{
		if (is_space(line[i]))
		{
			++i;
			continue ;
		}
		else if (is_special_char(line[i]))
			len = handle_special_token(line, i, &head);
		else if (line[i] == '\'' || line[i] == '"')
			len = handle_quoted_token(line, i, &head);
		else
			len = handle_word_token(line, i, &head);
		if (len < 0)
			return (free_tokens(head), NULL);
		i += len;
	}
	return (head);
}
