/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:21 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/05 13:55:57 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../library/gnl/get_next_line.h"
# include "utils.h"

extern volatile sig_atomic_t	g_received_signal;

t_shell			*init_shell(char **envp);
t_token			*tokenize(char *line, bool *possible_mem_error);
t_token			*create_token(const char *t_data, t_token_type t_type);
t_token			*add_token(t_token **head, t_token *new_token);
t_token			*last_token(t_token *head);
int				handle_quots_token(char *line, int i, t_token **head);
int				get_word_len_with_quotes(const char *line);
int				count_tokens(t_token *token);
char			*ps_path(t_shell *shell);

#endif
