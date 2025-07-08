/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 22:09:46 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/09 01:52:01 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token	*add_token(t_token **head, t_token *new_token)
{
	t_token	*last;

	if (!new_token)
		return (last_token(*head));
	if (!*head)
	{
		*head = new_token;
		new_token->prev_token = NULL;
		return (new_token);
	}
	last = last_token(*head);
	last->next_token = new_token;
	new_token->prev_token = last;
	return (last_token(last));
}

t_token	*last_token(t_token *head)
{
	t_token	*last;

	if (!head)
		return (NULL);
	last = head;
	while (last->next_token)
		last = last->next_token;
	return (last);
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next_token;
		free(tmp->token_data);
		free(tmp);
	}
}

void	free_token(t_token *token)
{
	if (token->token_data)
	{
		free(token->token_data);
		token->token_data = NULL;
	}
}
