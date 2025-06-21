/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:26:16 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/21 19:54:08 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	last_is_redirection(t_token *head)
{
	t_token	*last;

	last = head;
	while (last->next_token)
		last = last->next_token;
	if (last->token_redirect_type != REDIRECT_NONE)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (true);
	}
	return (false);
}

bool	invalid_operands(t_token *head)
{
	t_token	*token;

	token = head;
	while (token && token->next_token)
	{
		if (token->token_operator_type != OPERATOR_NONE && token->next_token->token_type != TOKEN_WORD)
		{
			printf("minishell: syntax error near unexpected token `%s'\n", token->next_token->token_data);
			return (true);
		}
		token = token->next_token;
	}
	return (false);
}
