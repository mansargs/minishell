/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:26:16 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/27 02:31:03 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	last_is_redirection(t_token *token)
{
	if (!token->next_token && token->token_type == TOKEN_REDIRECT)
	{
		printf("%s `newline'\n", SYN_ERR);
		return (true);
	}
	return (false);
}

// bool	redirection_after_redirection(t_token *head)
// {
// 	t_token	*tmp;

// 	tmp = head;
// 	while (tmp->next_token)
// 	{
// 		if (tmp->token_type == TOKEN_REDIRECT
// 			&& tmp->next_token-> token_type == TOKEN_REDIRECT)
// 		{
// 			printf("%s `%s'\n", SYN_ERR, tmp->next_token->token_data);
// 			return (true);
// 		}
// 		tmp = tmp->next_token;
// 	}
// 	return (false);
// }
