/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:57:34 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/11 17:02:34 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	append_back_list(t_token **list, t_token *token)
{
	t_token	*last;

	if (!*list)
	{
		*list = token;
		return ;
	}
	last = last_token(*list);
	last->next_token = token;
	token->prev_token = last;
}

static bool	handle_redirection(t_ast *branch, t_token **temp)
{
	if (!(*temp)->file_name)
	{
		(*temp)->file_name = ft_strdup((*temp)->next_token->token_data);
		if (!(*temp)->file_name)
			return (false);
	}
	branch->tokens = (*temp)->next_token->next_token;
	free_token(&(*temp)->next_token);
	(*temp)->next_token = NULL;
	append_back_list(&branch->redir, *temp);
	*temp = branch->tokens;
	return (true);
}

bool	command_redirection_division(t_ast *branch)
{
	t_token	*temp;

	temp = branch->tokens;
	while (temp)
	{
		if (temp->token_type == TOKEN_REDIRECT)
		{
			if (!handle_redirection(branch, &temp))
				return (false);
		}
		else
		{
			branch->tokens = temp->next_token;
			temp->next_token = NULL;
			temp->prev_token = NULL;
			append_back_list(&branch->cmd, temp);
			temp = branch->tokens;
		}
	}
	return (true);
}
