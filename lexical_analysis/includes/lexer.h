/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:17 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/18 00:53:28 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "token.h"
# include "token_type.h"

typedef struct s_token	t_token;
typedef enum e_token_type	t_token_type;
typedef enum e_token_class	t_token_class;

bool			is_space(char tok);
bool			is_redirect(char tok);
bool			is_special_char(char tok);
void			free_tokens(t_token *head);
bool			is_special_operator(char tok);
void			add_token(t_token **head, t_token *new_token);
void			add_token(t_token **head, t_token *new_token);
t_token_type	get_token_type(const char *token, int len);
t_token_type	single_token_type(const char *token);
t_token_type	double_token_type(const char *token);
t_token_class	get_token_class(char token);
t_token			*tokenize(char *line);
bool			wait_for_input_if_need(char **line);

#endif
