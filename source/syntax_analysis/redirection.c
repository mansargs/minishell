/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:26:16 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/24 13:20:42 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	last_is_redirection(t_token *head)
{
	t_token	*curr;

	curr = head;
	while (curr)
	{
		if (curr->token_type == TOKEN_REDIRECT && (!curr->next_token
				|| curr->next_token->token_type != TOKEN_WORD))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (true);
		}
		curr = curr->next_token;
	}
	return (false);
}

bool	redirection_after_redirection(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp->next_token)
	{
		if (tmp->token_type == TOKEN_REDIRECT
			&& tmp->next_token-> token_type == TOKEN_REDIRECT)
		{
			printf("minishell: syntax error near unexpected token `%s'\n",
				tmp->next_token->token_data);
			return (true);
		}
		tmp = tmp->next_token;
	}
	return (false);
}
