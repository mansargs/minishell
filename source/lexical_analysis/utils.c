/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 22:09:46 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/02 00:40:10 by alisharu         ###   ########.fr       */
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
	t_token	*temp;

	while (head)
	{
		temp = head;
		head = head->next_token;
		free_token(&temp);
	}
}

void	free_token(t_token **token)
{
	if ((*token)->token_data)
	{
		free((*token)->token_data);
		(*token)->token_data = NULL;
	}
	if ((*token)->file_name)
	{
		free((*token)->file_name);
		(*token)->file_name = NULL;
	}
	free(*token);
	*token = NULL;
}

int	count_tokens(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->token_type == TOKEN_WORD)
			count++;
		token = token->next_token;
	}
	return (count);
}
