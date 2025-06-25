/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:50:59 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/26 02:51:15 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

// bool	first_is_operator(t_token *head)
// {
// 	if (!head)
// 		return (false);
// 	if (head->token_type == TOKEN_OPERATOR
// 		&& head->token_operator_type != OPERATOR_PAREN_OPEN)
// 		return (printf("%s `%s'\n", SYN_ERR, head->token_data), true);
// 	return (false);
// }

// bool	operator_after_operator(t_token *head)
// {
// 	t_token	*tmp;

// 	tmp = head;
// 	while (tmp->next_token)
// 	{
// 		if (tmp->token_type == TOKEN_OPERATOR
// 			&& tmp->next_token->token_type == TOKEN_OPERATOR
// 			&& tmp->next_token->token_operator_type != OPERATOR_PAREN_OPEN
// 			&& tmp->next_token->token_operator_type != OPERATOR_PAREN_CLOSE)
// 			return (printf("%s `%s'\n", SYN_ERR, tmp->next_token->token_data),
// 				true);
// 		tmp = tmp->next_token;
// 	}
// 	return (false);
// }

// bool	operator_after_redirection(t_token *head)
// {
// 	t_token	*tmp;

// 	tmp = head;
// 	while (tmp->next_token)
// 	{
// 		if (tmp->token_type == TOKEN_REDIRECT
// 			&& tmp->next_token->token_type == TOKEN_OPERATOR)
// 			return (printf("%s `%s'\n", SYN_ERR,
// 					tmp->next_token->token_data), true);
// 		tmp = tmp->next_token;
// 	}
// 	return (false);
// }

bool	operator_after_open_paren(t_token *token)
{
	if (token->token_operator_type == OPERATOR_PAREN_OPEN
		&& token->next_token->token_operator_type != OPERATOR_PAREN_OPEN
		&& token->token_type == TOKEN_OPERATOR)
		return (printf("%s `%s'\n", SYN_ERR, token->next_token->token_data), true);
	return (false);
}

bool	operator_before_close_paren(t_token *token)
{
	if (token->token_type == TOKEN_OPERATOR
		&& token->token_operator_type != OPERATOR_PAREN_CLOSE
		&& token->next_token
		&& token->next_token->token_operator_type == OPERATOR_PAREN_CLOSE)
		return (printf("%s `%s'\n", SYN_ERR, token->next_token->token_data), true);
	return (false);
}
