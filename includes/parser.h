/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:22:46 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/09 00:43:40 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "syntax.h"

typedef struct redirection
{
	t_token	*redirect;
	char	*filename;
	t_token	*next;
}			t_redirection;

typedef struct ast
{
	t_token			*command;
	struct ast		*left_side;
	struct ast		*right_side;
	t_redirection	*redirect;
}					t_ast;

t_ast	*builing_ast(t_token	*head);

#endif


