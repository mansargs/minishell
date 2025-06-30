/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 03:03:48 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/30 13:04:58 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static bool	invalid_word(const t_token *token)
{
	if (token->next_token && token->next_token->token_operator_type == OPERATOR_PAREN_OPEN)
		return (printf("%s `('\n", SYN_ERR), true);
	return (false);
}

static bool	redirection_secondary_errors(const t_token *token)
{
	if (!token->next_token)
		return (printf("%s `newline'\n", SYN_ERR), true);
	if (invalid_redirect(token))
		return (true);
}

static invalid_open_parenthesis(const t_token *token)
{
	if (token->next_token && token->next_token->token_operator_type == OPERATOR_PAREN_CLOSE)
		return (printf("%s `%s'\n", SYN_ERR, token->next_token->token_data), true);
	
}


bool	secondary_syntax_errors(t_token *token)
{
	if (token->token_type == TOKEN_REDIRECT && redirection_secondary_errors(token))
			return (true);
	if (token->token_type == TOKEN_WORD && invalid_word(token))
			return (true);
	if (token->token_operator_type == OPERATOR_PAREN_OPEN)
	return (false);
}
