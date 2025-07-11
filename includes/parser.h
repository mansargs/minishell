/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:22:46 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/11 16:32:17 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "syntax.h"

typedef struct s_ast
{
	t_token			*tokens;
	struct s_ast	*left_side;
	struct s_ast	*right_side;
	t_token			*cmd;
	t_token			*redir;
}					t_ast;

t_ast	*building_ast(t_token	*head);
bool	logic_division(t_ast **branch, t_token *head);
bool	command_redirection_division(t_ast *branch);
bool	division_into_parenthesis(t_ast *branch);

#endif
