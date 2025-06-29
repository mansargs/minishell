/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 03:03:48 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/30 03:05:46 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static bool	invalid_word(const t_token *token)
{
	if (token->next_token && token->next_token->token_operator_type == OPERATOR_PAREN_OPEN)
		return (printf("%s `('\n", SYN_ERR), true);
	return (false);
}

static bool	redirection_second_check(const t_token *token)
{
	if (!token->next_token)
		return (printf("%s `newline'\n", SYN_ERR), true);
	if (token->next_token && token->next_token->token_type == TOKEN_OPERATOR)
		return (printf("%s `newline'\n", SYN_ERR), true);
}
