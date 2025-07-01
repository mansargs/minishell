/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 03:03:48 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/01 13:29:07 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

// static bool	invalid_word(const t_token *token)
// {
// 	if (token->next_token && token->next_token->token_operator_type == OPERATOR_PAREN_OPEN)
// 		return (printf("%s `('\n", SYN_ERR), true);
// 	return (false);
// }

// static int	count_parenthesis(t_token *token)
// {
// 	int		count;
// 	t_token	*temp;

// 	count = 0;
// 	temp = token;
// 	while (temp)
// 	{
// 		if (temp->token_operator_type == OPERATOR_PAREN_OPEN)
// 			++count;
// 		else if (temp->token_operator_type == OPERATOR_PAREN_CLOSE)
// 			--count;
// 		temp = temp->prev_token;
// 	}
// 	return (count);
// }

bool	secondary_syntax_errors(const t_token *token, int	*opened_parenthesis)
{
	if (token->token_operator_type == OPERATOR_PAREN_OPEN)
		++*opened_parenthesis;
	if (token->token_operator_type == OPERATOR_PAREN_CLOSE)
		--*opened_parenthesis;
	if (token->token_type == TOKEN_REDIRECT && invalid_redirect(token, NOT_STRICT))
			return (true);
	if (token->token_operator_type == OPERATOR_PAREN_CLOSE && *opened_parenthesis < 0)
			return (printf("%s `)'\n", SYN_ERR), true);
	if (token->token_operator_type == OPERATOR_PAREN_OPEN && token->prev_token && token->prev_token->token_type == TOKEN_WORD)
			return (printf("%s `('\n", SYN_ERR), true);
	if (token->token_type == TOKEN_OPERATOR && invalid_operator(token, NOT_STRICT))
		return (true);
	return (false);
}
