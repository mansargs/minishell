/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:22:46 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/09 17:04:53 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "syntax.h"

typedef struct redirection
{
	t_token				*token;
	char				*filename;
	struct redirection	*next;
}			t_redirection;

typedef struct ast
{
	t_token			*command;
	struct ast		*left_side;
	struct ast		*right_side;
	t_redirection	*redirect;
}					t_ast;

t_ast	*builing_ast(t_token	*head);
bool	logic_division(t_ast **branch, t_token *head);
bool	command_redirection_division(t_ast *branch);
bool	division_into_parenthesis(t_ast **branch, t_token *head);

#endif
