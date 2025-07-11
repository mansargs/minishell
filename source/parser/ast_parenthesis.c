/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parenthesis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:56:06 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/11 17:01:50 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_token	*find_rparen(t_token *tokens)
{
	t_token	*temp;
	t_token	*rparen;

	temp = tokens;
	rparen = NULL;
	while (temp)
	{
		if (temp->token_paren_type == PAREN_CLOSE)
			rparen = temp;
		temp = temp->next_token;
	}
	return (rparen);
}

static void	cut_paren_block(t_token *lparen, t_token *rparen)
{
	t_token	*paren_content;

	paren_content = lparen->next_token;
	if (paren_content)
		paren_content->prev_token = NULL;
	if (rparen->prev_token)
		rparen->prev_token->next_token = NULL;
	lparen->next_token = rparen;
	rparen->prev_token = lparen;
	rparen->next_token = NULL;
}

bool	division_into_parenthesis(t_ast *branch)
{
	t_token	*lparen;
	t_token	*rparen;
	t_token	*paren_content;
	t_token	*after_close;

	lparen = branch->tokens;
	rparen = find_rparen(lparen);
	if (!rparen || lparen == rparen || !lparen->next_token)
		return (false);
	paren_content = lparen->next_token;
	after_close = rparen->next_token;
	cut_paren_block(lparen, rparen);
	if (after_close)
	{
		after_close->prev_token = NULL;
		branch->tokens = after_close;
		if (!command_redirection_division(branch))
			return (false);
	}
	branch->cmd = lparen;
	if (!logic_division(&branch->left_side, paren_content))
		return (false);
	return (true);
}
