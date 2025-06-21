/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:21 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/21 12:32:08 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../../libft/libft.h"

//enum types
typedef enum e_token_type
{
	TOKEN_WORD = 0,			// 0  =>  pxik (command/arg)
	TOKEN_OPERATOR = 1,		// 1  =>  &&, ||, |
	TOKEN_REDIRECT = 2,		// 2  =>  <, >, >>, <<
	TOKEN_META = 3,			// 3  =>  $, ', ", \, ;
}	t_token_type;

typedef enum e_operator_type
{
	OPERATOR_PIPE = 4,			// 4  =>  "|"
	OPERATOR_OR,				// 5  =>  "||"
	OPERATOR_AND,				// 6  =>  "&&"
	OPERATOR_AMP,				// 7  =>  "&"
	OPERATOR_DOLLAR,			// 8  =>  "$"
	OPERATOR_PAREN_OPEN,		// 9  =>  "("
	OPERATOR_PAREN_CLOSE,		// 10 =>  ")"
}	t_operator_type;

typedef enum e_redirection_type
{
	REDIRECT_IN = 11,			// 11  =>  "<"
	REDIRECT_OUT,				// 12  =>  ">"
	REDIRECT_APPEND,			// 13  =>  ">>"
	REDIRECT_HEREDOC,			// 14  =>  "<<"
}	t_redirection_type;

//main struct
typedef struct s_token
{
	char				*token_data;
	t_token_type		token_type;
	t_operator_type		token_operator_type;
	t_redirection_type	token_redirect_type;
	struct s_token		*next_token;
}	t_token;

//prototypes
t_token			*tokenize(char *line);
t_token			*create_token(const char *t_data, t_token_type t_type);
t_token_type	get_token_type(const char *token, int len);
t_token_type	single_token_type(const char *token);
t_token_type	double_token_type(const char *token);
bool			is_space(char tok);
bool			is_redirect(char tok);
bool			is_special_char(char tok);
bool			is_special_operator(char tok);
bool			wait_for_input_if_need(char **line);
void			free_tokens(t_token *head);
void			add_token(t_token **head, t_token *new_token);
int				extract_quoted_string(char *line, int i, char *str);
int				handle_quoted_token(char *line, int i, t_token **head);
int				skip_variable(const char *line, int i);

#endif
