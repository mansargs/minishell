/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:23 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/16 13:44:58 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"

t_token_type	single_token_type(const char *token)
{
	if (*token == '|')
		return (TOKEN_PIPE);
	if (*token == '&')
		return (TOKEN_SINGLE_AND);
	if (*token == '(')
		return (TOKEN_PAREN_OPEN);
	if (*token == ')')
		return (TOKEN_PAREN_CLOSE);
	if (*token == '<')
		return (TOKEN_REDIRECT_IN);
	if (*token == '>')
		return (TOKEN_REDIRECT_OUT);
	if (*token == '$')
		return (TOKEN_DOLLAR);
	if (*token == '\'')
		return (TOKEN_SINGLE_QUOTE);
	if (*token == '"')
		return (TOKEN_DOUBLE_QUOTE);
	if (*token == '\\')
		return (TOKEN_ESCAPE);
	return (TOKEN_WORD);
}

t_token_type	double_token_type(const char *token)
{
	if (ft_strncmp(token, "&&", 2) == 0)
		return (TOKEN_AND);
	if (ft_strncmp(token, "||", 2) == 0)
		return (TOKEN_OR);
	if (ft_strncmp(token, ">>", 2) == 0)
		return (TOKEN_APPEND);
	if (ft_strncmp(token, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	return (TOKEN_WORD);
}

t_token_type	get_token_type(const char *token, int len)
{
	if (len == 1)
		return (single_token_type(token));
	else if (len == 2)
		return (double_token_type(token));
	return (TOKEN_WORD);
}

t_token_class	get_token_class(char token)
{
	if (token == '|' || token == '&' || token == '(' || token == ')')
		return (TOKEN_CLASS_OPERATOR);
	else if (token == '<' || token == '>')
		return (TOKEN_CLASS_REDIRECTION);
	else if (token == '$' || token == '\'' || token == '"' || token == '\\')
		return (TOKEN_CLASS_META);
	return (TOKEN_CLASS_WORD);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*tmp;

	if (!head || !new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	tmp = *head;
	while (tmp->next_token)
		tmp = tmp->next_token;
	tmp->next_token = new_token;
}

