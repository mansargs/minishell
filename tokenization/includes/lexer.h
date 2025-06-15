/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:17 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/15 14:54:17 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "token.h"
# include "token_type.h"

typedef struct s_token	t_token;
typedef enum e_token_type	t_token_type;
typedef enum e_token_class	t_token_class;

int				is_space(char tok);
int				is_redirect(char tok);
int				is_special_char(char tok);
void			free_tokens(t_token *head);
int				is_special_operator(char tok);
void			add_token(t_token **head, t_token *new_token);
void			add_token(t_token **head, t_token *new_token);
t_token_type	get_token_type(const char *token, int len);
t_token_type	single_token_type(const char *token);
t_token_type	double_token_type(const char *token);
t_token_class	get_token_class(char token);
t_token			*tokenize(char *line);

#endif
