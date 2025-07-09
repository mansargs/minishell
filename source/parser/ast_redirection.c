/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:57:34 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/09 17:03:41 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	handle_redir_filename(t_token *token, t_redirection *redir)
{
	if (token->token_redirect_type == REDIRECT_HEREDOC)
		redir->filename = token->file_name;
	else
	{
		redir->filename = ft_strdup(token->next_token->token_data);
		if (!redir->filename)
			return (false);
	}
	return (true);
}

static bool	remove_redirection(t_ast *branch, t_token *token,
								t_redirection *redir)
{
	t_token	*pre_redir;
	t_token	*next_next;

	pre_redir = token->prev_token;
	next_next = token->next_token->next_token;
	redir->token = token;
	if (!handle_redir_filename(token, redir))
		return (false);
	free_token(&token->next_token);
	token->next_token = NULL;
	if (pre_redir)
	{
		pre_redir->next_token = next_next;
		if (next_next)
			next_next->prev_token = pre_redir;
	}
	else
	{
		branch->command = next_next;
		if (next_next)
			next_next->prev_token = NULL;
	}
	return (true);
}

static void	append_redirection(t_redirection **head, t_redirection *new)
{
	t_redirection	*last;

	if (!*head)
		*head = new;
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

bool	command_redirection_division(t_ast *branch)
{
	t_token			*temp;
	t_redirection	*new_redir;

	temp = branch->command;
	while (temp)
	{
		if (temp->token_type == TOKEN_REDIRECT)
		{
			new_redir = ft_calloc(1, sizeof(t_redirection));
			if (!new_redir || !remove_redirection(branch, temp, new_redir))
				return (false);
			append_redirection(&branch->redirect, new_redir);
			temp = branch->command;
			continue ;
		}
		temp = temp->next_token;
	}
	return (true);
}

bool	division_into_parenthesis(t_ast **branch, t_token *head)
{
	t_token	*temp;

	temp = head;
	head = head->next_token;
	free_token(&temp);
	temp = last_token(head);
	temp->prev_token->next_token = NULL;
	free_token(&temp);
	if (!logic_division(branch, head))
		return (false);
	return (true);
}
