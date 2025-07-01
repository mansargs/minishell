/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 03:03:48 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/01 22:17:21 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

void	manage_parenthesis(const t_token *token, int *opened_parenthesis)
{
	if (token->token_operator_type == OPERATOR_PAREN_OPEN)
		++*opened_parenthesis;
	if (token->token_operator_type == OPERATOR_PAREN_CLOSE)
		--*opened_parenthesis;
}

bool	secondary_syntax_errors(const t_token *token, int	*opened_parenthesis)
{
	manage_parenthesis(token, opened_parenthesis);
	if (token->token_type == TOKEN_REDIRECT
		&& invalid_redirect(token, NOT_STRICT))
		return (true);
	if (token->token_operator_type == OPERATOR_PAREN_CLOSE
		&& *opened_parenthesis < 0)// )ete avel pak ) qcum em error
		return (printf("%s `)'\n", SYN_ERR), true);
	if (*opened_parenthesis > 0)// (ete avel bac ( qcum em error
		return (printf("%s `('\n", SYN_ERR), true);
	if (token->token_operator_type == OPERATOR_PAREN_OPEN
		&& token->prev_token && token->prev_token->token_type == TOKEN_WORD)
		return (printf("%s `('\n", SYN_ERR), true);
	if (token->token_type == TOKEN_OPERATOR
		&& invalid_operator(token, NOT_STRICT))
		return (true);
	return (false);
}
