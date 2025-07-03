/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:24:51 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/03 14:13:45 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# include "token.h"
# include <fcntl.h>

#define STRICT 1
#define NOT_STRICT 0

char	*open_heredoc(const t_token *tokens);
t_token	*last_token(t_token *head);
bool	should_I_wait(const t_token *last_token);
bool	syntax_and_heredoc(t_token *tokens, char **line);
bool	wait_for_input(t_token *last, char **line);
bool	invalid_open_parenthesis(const t_token *token);

bool	invalid_word(const t_token *token);
bool	invalid_redirect(const t_token *token, const int strict_flag);
bool	invalid_operator(const t_token *token, const int strict_flag);
bool	strict_syntax_errors(t_token *tokens);

bool	secondary_syntax_errors(const t_token *token, int *opened_parenthesis);
int		handle_quoted(t_token *token);


#endif
