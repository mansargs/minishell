/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:26:16 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/21 18:57:10 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	last_is_redirection(t_token *head)
{
	t_token	*last;

	last = head;
	while (last->next_token)
		last = last->next_token;
	printf ("%d\n", last->token_redirect_type);
	printf ("%s\n", last->token_data);
	if (last->token_redirect_type > REDIRECTION_NONE)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (true);
	}
	return (false);
}
