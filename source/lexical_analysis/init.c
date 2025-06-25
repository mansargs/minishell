/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:23 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/26 00:58:47 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static t_operator_type	get_operator_type(const char *token, int len)
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
		// if (*token == '&')
		// 	return (OPERATOR_AMP);
		if (*token == '(')
			return (OPERATOR_PAREN_OPEN);
		if (*token == ')')
			return (OPERATOR_PAREN_CLOSE);
	}
	return (0);
}

static t_redirection_type	get_redirection_type(const char *token, int len)
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
	return (0);
}

t_token_type	get_token_type(const char *token, int len)
{
	if (len == 1)
	{
		if (*token == '|' || *token == '&' || *token == '('
			|| *token == ')')
			return (TOKEN_OPERATOR);
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

t_token	*create_token(const char *t_data, t_token_type t_type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->token_data = ft_strdup(t_data);
	token->token_type = t_type;
	if (t_type == TOKEN_OPERATOR)
		token->token_operator_type
			= get_operator_type(t_data, ft_strlen(t_data));
	else if (t_type == TOKEN_REDIRECT)
		token->token_redirect_type
			= get_redirection_type(t_data, ft_strlen(t_data));
	token->next_token = NULL;
	return (token);
}
