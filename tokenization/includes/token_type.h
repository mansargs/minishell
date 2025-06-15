/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:19 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/15 16:43:20 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_TYPE_H
# define TOKEN_TYPE_H

# include "lexer.h"
# include "token.h"

typedef enum e_token_class
{
	TOKEN_CLASS_WORD,			// word
	TOKEN_CLASS_OPERATOR,		// &&, ||, |
	TOKEN_CLASS_REDIRECTION,	// <, >, >>, <<
	TOKEN_CLASS_META,			// $, ', ", \.
}			t_token_class;

typedef enum e_token_type
{
	TOKEN_WORD,				// word
	TOKEN_PIPE,				// |
	TOKEN_OR,				// ||
	TOKEN_AND,				// &&
	TOKEN_REDIRECT_IN,		// <
	TOKEN_REDIRECT_OUT,		// >
	TOKEN_APPEND,			// >>
	TOKEN_HEREDOC,			// <<
	TOKEN_SINGLE_AND,		// &
	TOKEN_DOLLAR,			// $
	TOKEN_SINGLE_QUOTE,		// '
	TOKEN_DUBLE_QUOTE,		// "
	TOKEN_ESCAPE,			// \.
	TOKEN_PAREN_OPEN,		// (
	TOKEN_PAREN_CLOSE,		// )
	TOKEN_EOF
}			t_token_type;

#endif