/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:38:09 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/26 02:51:36 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	syntax_analysis(t_token *token)
{
	if (last_is_redirection(token))
		return (true);
	// if (operator_before_paren(token))
	// 	return (true);
	if (empty_parens(token))
		return (true);
	if (operator_after_open_paren(token))
		return (true);
	if (operator_before_close_paren(token))
		return (true);
	if (close_paren_without_open(token))
		return (true);
	return (false);
}
