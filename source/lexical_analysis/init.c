/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:23 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/03 02:47:07 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static t_operator_type	get_operator_type(const char *token, const int len)
{
	if (len == 2)
	{
		if (!ft_strncmp(token, "&&", 2))
			return (OPERATOR_AND);
		if (!ft_strncmp(token, "||", 2))
			return (OPERATOR_OR);
	}
	else if (len == 1)
	{
		if (*token == '|')
			return (OPERATOR_PIPE);
	}
	return (OPERATOR_NONE);
}

static t_redirection_type	get_redirection_type(const char *token, const int len)
{
	if (len == 2)
	{
		if (!ft_strncmp(token, ">>", 2))
			return (REDIRECT_APPEND);
		if (!ft_strncmp(token, "<<", 2))
			return (REDIRECT_HEREDOC);
	}
	else if (len == 1)
	{
		if (*token == '<')
			return (REDIRECT_IN);
		if (*token == '>')
			return (REDIRECT_OUT);
	}
	return (REDIRECT_NONE);
}

static t_paren_type	get_paren_type(const char *token)
{

	if (*token == '(')
		return (PAREN_OPEN);
	if (*token == ')')
		return (PAREN_CLOSE);
	return (PAREN_NONE);
}

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

t_token	*create_token(const char *t_data, t_token_type type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->token_data = ft_strdup(t_data);
	token->token_type = type;
	if (type == TOKEN_OPERATOR)
		token->token_operator_type
			= get_operator_type(t_data, ft_strlen(t_data));
	else if (type == TOKEN_REDIRECT)
		token->token_redirect_type
			= get_redirection_type(t_data, ft_strlen(t_data));
	else if (type == TOKEN_PAREN)
		token->token_paren_type
			= get_paren_type(t_data);
	token->next_token = NULL;
	return (token);
}
