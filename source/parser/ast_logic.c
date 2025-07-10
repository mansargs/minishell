/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_logic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:30:46 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/10 12:51:05 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	is_better_operator(t_token *temp, t_token *lowest)
{
	if (!lowest)
		return (true);
	if (temp->token_operator_type == OPERATOR_OR)
		return (true);
	if (temp->token_operator_type == OPERATOR_AND
		|| lowest->token_operator_type == OPERATOR_PIPE)
		return (true);
	return (false);
}

static t_token	*find_lowest_operator(t_token *head)
{
	t_token	*temp;
	t_token	*lowest;
	int		paren_depth;

	temp = head;
	lowest = NULL;
	paren_depth = 0;
	while (temp)
	{
		manage_parenthesis(temp, &paren_depth);
		if (temp->token_type == TOKEN_OPERATOR && !paren_depth
			&& is_better_operator(temp, lowest))
			lowest = temp;
		temp = temp->next_token;
	}
	return (lowest);
}

static bool	handle_leaf_branch(t_ast **branch, t_token *head)
{
	if (head->token_paren_type == PAREN_OPEN)
		return (division_into_parenthesis(branch, head));
	if (!command_redirection_division(*branch))
		return (false);
	(*branch)->command = head;
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
		if (lowest->prev_token)
			lowest->prev_token->next_token = NULL;
		if (!logic_division(&(*branch)->left_side, head)
			|| !logic_division(&(*branch)->right_side, right_head))
			return (false);
	}
	else if (!handle_leaf_branch(branch, head))
		return (false);
	return (true);
}

t_ast	*building_ast(t_token *head)
{
	t_ast	*tree;

	if (!logic_division(&tree, head))
		return (NULL);
	return (tree);
}
