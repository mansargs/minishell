/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:23 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/14 21:11:26 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token_class	classify_token_class(char token)
{
	if (token == '|' || token == '&' || token == '(' || token == ')')
		return (TOKEN_CLASS_OPERATOR);
	else if (token == '<' || token == '>')
		return (TOKEN_CLASS_REDIRECTION);
	else if (token == '$' || token == '\'' || token == '"' || token == '\\')
		return (TOKEN_CLASS_META);
	return (TOKEN_CLASS_WORD);
}

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
		return (TOKEN_DUBLE_QUOTE);
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

t_token_type	classify_token_type(const char *token, int len)
{
	if (len == 1)
		return (single_token_type(token));
	else if (len == 2)
		return (double_token_type(token));
	return (TOKEN_WORD);
}

