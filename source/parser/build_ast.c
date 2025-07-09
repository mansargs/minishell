/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:30:46 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/09 14:19:45 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	logic_division(t_ast **branch, t_token *head);

static t_token	*find_lowest_operator(t_token *head)
{
	t_token		*temp;
	t_token		*lowest;
	int			paren_depth;

	temp = head;
	lowest = NULL;
	paren_depth = 0;
	while(temp)
	{
		manage_parenthesis(temp, &paren_depth);
		if (temp->token_type == TOKEN_OPERATOR && !paren_depth)
		{
			if (lowest)
				if ((temp->token_operator_type == OPERATOR_AND && lowest->token_operator_type == OPERATOR_OR)
					|| temp->token_operator_type == OPERATOR_PIPE)
				{
				temp = temp->next_token;
				continue;
				}
		lowest = temp;
		}
		temp = temp->next_token;
	}
	return (lowest);
}

bool	division_into_parenthesis(t_ast **branch, t_token *head)
{
	t_token	*temp;

	temp  = head;
	head = head->next_token;
	free_token(&temp);
	temp = last_token(head);
	temp->prev_token->next_token = NULL;
	free_token(&temp);
	if (!logic_division(branch, head))
		return (false);
	return (true);
}

bool remove_redirection(t_ast *branch, t_token *token, t_redirection *redir)
{
	t_token *pre_redir;
	t_token *next_next;

	pre_redir = token->prev_token;
	next_next = token->next_token->next_token;

	redir->token = token;
	if (token->token_redirect_type == REDIRECT_HEREDOC)
		redir->filename = token->file_name;
	else
	{
		redir->filename = ft_strdup(token->next_token->token_data);
		if (!redir->filename)
			return (false);
	}

	free_token(&token->next_token);
	token->next_token = NULL;

	// Reconnect token list
	if (pre_redir)
	{
		pre_redir->next_token = next_next;
		if (next_next)
			next_next->prev_token = pre_redir;
	}
	else
	{
		// token is head, update head pointer
		branch->command = next_next;
		if (next_next)
			next_next->prev_token = NULL;
	}

	return (true);
}

bool	command_redirection_division(t_ast *branch)
{
	t_token			*temp;
	t_redirection	*new_redir;
	t_redirection	*last_redir;

	temp = branch->command;
	last_redir = NULL;
	while (temp)
	{
		if (temp->token_type == TOKEN_REDIRECT)
		{
			new_redir = ft_calloc(1, sizeof(t_redirection));
			if (!new_redir)
				return (false);
			if (!remove_redirection(branch, temp, new_redir))
				return (false);
			if (!branch->redirect)
				branch->redirect = new_redir;
			else
			{
				last_redir = branch->redirect;
				while (last_redir->next)
					last_redir = last_redir->next;
				last_redir->next = new_redir;
			}
			temp = branch->command;
			continue;
		}
		temp = temp->next_token;
	}
	return (true);
}

bool	logic_division(t_ast **branch, t_token *head)
{
	t_token	*lowest;
	t_token	*right_head;

	*branch = ft_calloc(1, sizeof(t_ast));
	if (!*branch)
		return (false);
	(*branch)->command = head;
	lowest = find_lowest_operator(head);
	if (lowest)
	{
		right_head = lowest->next_token;
		lowest->next_token = NULL;
		(*branch)->command = lowest;
		lowest->prev_token->next_token = NULL;
		logic_division(&(*branch)->left_side, head);
		logic_division(&(*branch)->right_side, right_head);
	}
	else
	{
		if (head->token_paren_type == PAREN_OPEN)
		{
			if (!division_into_parenthesis(branch, head))
				return (false);
		}
		else
		{
			(*branch)->command = head;
			if (!command_redirection_division(*branch))
				return (false);
		}

	}
	return (true);
}

t_ast	*builing_ast(t_token	*head)
{
	t_ast	*tree;

	if (!logic_division(&tree, head))
		return (NULL);

	return (tree);
}
