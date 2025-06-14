/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:35:41 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/14 23:20:19 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	is_space(char tok)
{
	return (tok == ' ' || tok == '\t' || tok == '\n'
		|| tok == '\v' || tok == '\f' || tok == '\r');
}

int	is_special_char(char tok)
{
	return (tok == '|' || tok == '&' || tok == '<' || tok == '>'
		|| tok == '(' || tok == ')' || tok == '\'' || tok == '"'
		|| tok == '\\' || tok == '$');
}

int	is_redirect(char tok)
{
	return (tok == '<' || tok == '>');
}

int	is_special_operator(char tok)
{
	return (tok == '&' || tok == '(' || tok == ')' || tok == '|' || tok == ';');
}

t_token	*tokenize(char *line)
{
	t_token_class	cls;
	t_token_type	typ;
	t_token			*tok;
	t_token			*head;
	char			*substr;
	int				len;
	int				i;

	head = NULL;
	i = -1;
	while (line[++i] != '\0')
	{
		if (is_space(line[i]))
			continue ;
		if (is_special_char(line[i]))
		{
			len = 1;
			if ((line[i] == '&' && line[i + 1] == '&')
				|| (line[i] == '|' && line[i + 1] == '|')
				|| (line[i] == '<' && line[i + 1] == '<')
				|| (line[i] == '>' && line[i + 1] == '>'))
				len = 2;
			cls = classify_token_class(line[i]);
			typ = classify_token_type(&line[i], len);
			substr = ft_substr(&line[i], 0, len);
			tok = create_token(substr, cls, typ);
			free(substr);
			if (!tok)
				return (NULL);
			add_token(&head, tok);
			i += len - 1;
			continue ;
		}
		len = word_len(&line[i]);
		cls = TOKEN_CLASS_WORD;
		typ = TOKEN_WORD;
		substr = ft_substr(&line[i], 0, len);
		tok = create_token(substr, cls, typ);
		free(substr);
		if (!tok)
			return (NULL);
		add_token(&head, tok);
		i += len - 1;
	}
	return (head);
}


