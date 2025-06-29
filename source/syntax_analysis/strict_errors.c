/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strict_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:55:20 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/30 02:55:58 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	strict_syntax_errors(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		if (temp->token_type == TOKEN_REDIRECT)
			if (invalid_redirect(temp))
				return (true);
		if (temp->token_type == TOKEN_OPERATOR)
			if (invalid_operator(temp))
				return (true);
		temp = temp->next_token;
	}
	return (false);
}
