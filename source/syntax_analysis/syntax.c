/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:38:09 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/23 13:49:07 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	syntax_analysis(t_token *tokens)
{
	if (operator_after_operator(tokens))
		return (true);
	if (redirection_after_redirection(tokens))
		return (true);
	if (operator_after_redirection(tokens))
		return (true);
	if (last_is_redirection(tokens))
		return (true);
	if (first_is_operator(tokens))
		return (true);
	if (empty_parens(tokens))
		return (true);
	if (operator_after_open_paren(tokens))
		return (true);
	if (operator_before_close_paren(tokens))
		return (true);
	if (close_paren_without_open(tokens))
		return (true);
	return (false);
}
