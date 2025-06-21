/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:21 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/21 18:51:42 by mansargs         ###   ########.fr       */
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
# include "libft.h"

//enum types
typedef enum e_token_type
{
	TOKEN_WORD,					//  pxik (command/arg)
	TOKEN_OPERATOR,				//  &&, ||, |
	TOKEN_REDIRECT,				//  <, >, >>, <<
}	t_token_type;

typedef enum e_operator_type
{
	OPERATOR_NONE,
	OPERATOR_PIPE,				//  "|"
	OPERATOR_OR,				//  "||"
	OPERATOR_AND,				//  "&&"
	OPERATOR_AMP,				//  "&"
	OPERATOR_PAREN_OPEN,		//  "("
	OPERATOR_PAREN_CLOSE,		//  ")"
}	t_operator_type;

typedef enum e_redirection_type
{
	REDIRECTION_NONE,
	REDIRECT_IN,				//    >"
	REDIRECT_OUT,				//2  ">"
	REDIRECT_APPEND,			//3  ">>"
	REDIRECT_HEREDOC,			//4  "<<"
}	t_redirection_type;

//main struct
typedef struct s_token
{
	char				*token_data;
	char				*input_name;
	int					is_temp;
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
