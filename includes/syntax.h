/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:24:51 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/01 21:05:34 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# include "token.h"
# include <fcntl.h>

char *open_heredoc(const t_token *tokens, unsigned int *index);
bool	should_I_wait(const t_token *last_token);
bool	syntax_and_heredoc(t_token *tokens, char **line);
bool	wait_for_input(t_token *last, char **line);
bool	invalid_open_parenthesis(const t_token *token);

bool	invalid_word(const t_token *token);
bool	invalid_redirect(const t_token *token, const int strict_flag);
bool	invalid_operator(const t_token *token, const int strict_flag);
bool	strict_syntax_errors(t_token *tokens);

bool	secondary_syntax_errors(const t_token *token, int *opened_parenthesis);

#define STRICT 1
#define NOT_STRICT 0

#endif
