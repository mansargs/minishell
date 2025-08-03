/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:21 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/04 02:28:53 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../library/libft/libft.h"
# include "../library/gnl/get_next_line.h"
# include "types.h"
# include "syntax.h"

# define SYN_ERR "minishell: syntax error near unexpected token"

extern volatile sig_atomic_t	g_received_signal;

bool			only_spaces(const char *str);
t_shell			*init_shell(char **envp);
t_token			*tokenize(char *line, bool *possible_mem_error);
t_token			*create_token(const char *t_data, t_token_type t_type);
t_token			*add_token(t_token **head, t_token *new_token);
t_token			*last_token(t_token *head);
bool			is_space(char tok);
bool			is_redirect(char tok);
bool			is_special_char(char tok);
bool			is_special_operator(char tok);
void			free_tokens(t_token **head);
int				handle_quots_token(char *line, int i, t_token **head);
int				skip_variable(const char *line, int i);
int				get_word_len_with_quotes(const char *line);
void			free_token(t_token **token);
int				count_tokens(t_token *token);
char			*ps_path(t_shell *shell);
void			free_shell(t_shell **shell);
void			conditional_free(t_shell **shell, bool ast, bool minishell);

#endif
