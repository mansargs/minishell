/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 03:03:48 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/06 19:15:26 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

void	manage_parenthesis(const t_token *token, int *opened_parenthesis)
{
	if (token->token_paren_type == PAREN_OPEN)
		++*opened_parenthesis;
	if (token->token_paren_type == PAREN_CLOSE)
		--*opened_parenthesis;
}

static bool	invalid_open_parenthesis(const t_token *token)
{
	if (token->prev_token && token->prev_token->token_type == TOKEN_WORD)
		return (print_error("("), true);
	if (token->next_token && (token->next_token->token_type == TOKEN_OPERATOR
			|| token->next_token->token_paren_type == PAREN_CLOSE))
		return (print_error(token->next_token->token_data), true);
	return (false);
}

static bool	invalid_close_parenthesis(const t_token *token, const int opened)
{
	if (opened < 0)
		return (print_error(")"), true);
	if (token->next_token && (token->next_token->token_paren_type == PAREN_OPEN
			|| token->next_token->token_type == TOKEN_WORD))
		return (print_error(token->next_token->token_data), true);
	if (token->prev_token && token->prev_token->token_type == TOKEN_REDIRECT)
		return (print_error(")"), true);
	return (false);
}

bool	secondary_syntax_errors(const t_token *token, int	*opened_parenthesis)
{
	manage_parenthesis(token, opened_parenthesis);
	if (token->token_type == TOKEN_REDIRECT
		&& invalid_redirect(token, NOT_STRICT))
		return (true);
	if (token->token_paren_type == PAREN_CLOSE
		&& invalid_close_parenthesis(token, *opened_parenthesis))
		return (true);
	if (token->token_type == TOKEN_OPERATOR
		&& invalid_operator(token, NOT_STRICT))
		return (true);
	if (token->token_paren_type == PAREN_OPEN
		&& invalid_open_parenthesis(token))
		return (true);
	if (!token->next_token && *opened_parenthesis > 0)
		return (print_error("newline"), true);
	return (false);
}
