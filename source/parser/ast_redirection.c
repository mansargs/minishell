/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:57:34 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/11 13:00:12 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	append_back_list(t_token **list, t_token *token)
{
	t_token *last;

	if (!*list)
		*list = token;
	else
	{
		last = last_token(*list);
		last->next_token = token;
		token->prev_token = last;
	}
}

bool	command_redirection_division(t_ast *branch)
{
	t_token	*temp;

	temp = branch->tokens;
	while (temp)
	{
		if (temp->token_type == TOKEN_REDIRECT)
		{
			if (!temp->file_name)
			{
				temp->file_name = ft_strdup(temp->next_token->token_data);
				if (!temp->file_name)
					return (false);
			}
			branch->tokens = temp->next_token->next_token;
			free_token(&temp->next_token);
			temp->next_token = NULL;
			append_back_list(&branch->redir, temp);
			temp = branch->tokens;
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

bool	division_into_parenthesis(t_ast **branch)
{
	t_token	*lparen;
	t_token	*rparen;
	t_token	*paren_content;
	t_token	*after_close;
	t_token	*temp;

	lparen = (*branch)->tokens;
	temp = (*branch)->tokens;

	while(temp)
	{
		if (temp->token_paren_type == PAREN_CLOSE)
			rparen = temp;
		temp = temp->next_token;
	}
	paren_content = lparen->next_token;
	after_close = rparen->next_token;

	lparen->next_token = rparen;
	rparen->next_token = NULL;

	if (after_close)
	{
		after_close->prev_token = NULL;
		(*branch)->tokens = after_close;
		if (!command_redirection_division(*branch))
			return (false);
	}
	paren_content->prev_token = NULL;
	rparen->prev_token->next_token = NULL;
	(*branch)->cmd = lparen;
	if (!logic_division(&(*branch)->left_side, paren_content))
		return (false);
	return (true);
}


