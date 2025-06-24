/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:24:51 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/24 17:43:08 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# include "token.h"

bool	syntax_analysis(t_token *tokens);
bool	first_is_operator(t_token *head);
bool	operator_after_operator(t_token *head);
bool	operator_after_redirection(t_token *head);
bool	last_is_redirection(t_token *head);
bool	redirection_after_redirection(t_token *head);
bool	operator_before_close_paren(t_token *head);
bool	operator_after_open_paren(t_token *head);
bool	close_paren_without_open(t_token *head);
bool	empty_parens(t_token *head);
bool	operator_before_paren(t_token *head);

#endif
