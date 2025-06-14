/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:17 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/14 23:18:14 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "token.h"
# include "token_type.h"

typedef struct s_token t_token;
typedef enum e_token_type t_token_type;
typedef enum e_token_class t_token_class;

void			add_token(t_token **head, t_token *new_token);
int				word_len(const char *line);
t_token			*create_token(const char *t_data, t_token_class t_class,
					t_token_type t_type);
t_token			*tokenize(char *line);
int				is_space(char tok);
int				is_special_char(char tok);
int				is_redirect(char tok);
int				is_special_operator(char tok);
void			add_token(t_token **head, t_token *new_token);
t_token_class	classify_token_class(char token);
t_token_type	single_token_type(const char *token);
t_token_type	double_token_type(const char *token);
t_token_type	classify_token_type(const char *token, int len);

#endif