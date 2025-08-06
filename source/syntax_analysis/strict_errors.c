/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strict_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:55:20 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/06 19:22:35 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

void	print_error(char *unexpented)
{
	ft_putstr_fd(SYN_ERR, STDERR_FILENO);
	ft_putstr_fd(" `", STDERR_FILENO);
	ft_putstr_fd(unexpented, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}

bool	invalid_redirect(const t_token *token, const int strict_flag)
{
	if (strict_flag)
	{
		if (token->next_token && token->next_token->token_type
			== TOKEN_REDIRECT)
			return (print_error(token->next_token->token_data), true);
		if (token->next_token && (token->next_token->token_type
				== TOKEN_OPERATOR || token->next_token->token_paren_type
				== PAREN_OPEN))
			return (print_error(token->next_token->token_data), true);
	}
	else
	{
		if (!token->next_token)
			return (print_error("newline"), true);
		if (token->prev_token && token->prev_token->token_paren_type
			== PAREN_CLOSE
			&& token->next_token->next_token
			&& token->next_token->next_token->token_type == TOKEN_WORD)
			return (print_error(token->next_token->next_token->token_data), true);
	}
	return (false);
}

bool	invalid_operator(const t_token *token, const int strict_flag)
{
	if (strict_flag)
	{
		if (!token->prev_token && token->token_type == TOKEN_OPERATOR)
			return (print_error(token->token_data), true);
		if (token->next_token
			&& token->next_token->token_type == TOKEN_OPERATOR)
			return (print_error(token->next_token->token_data), true);
		if (token->next_token && token->next_token->token_type
			== TOKEN_OPERATOR)
			return (print_error(token->next_token->token_data), true);
	}
	else
	{
		if (token->next_token && token->next_token->token_paren_type
			== PAREN_CLOSE)
			return (print_error(token->next_token->token_data), true);
		if (!token->next_token)
			return (print_error("newline"), true);
	}
	return (false);
}

bool	check_heredoc_case(t_shell *shell, t_token *token)
{
	t_token	*tmp;
	char	*parsed;
	int		open_flag;

	open_flag = 0;
	if (token->token_redirect_type == REDIRECT_HEREDOC
		&& token->next_token
		&& token->next_token->token_type == TOKEN_WORD)
	{
		tmp = token->next_token;
		parsed = open_quotes_heredoc(shell, tmp->token_data,
				&open_flag);
		if (!parsed)
			return (true);
		free(tmp->token_data);
		tmp->token_data = parsed;
	}
	return (false);
}

bool	strict_syntax_errors(t_shell *shell)
{
	t_token	*temp;

	temp = shell->tokens;
	while (temp)
	{
		if (temp->token_type == TOKEN_REDIRECT)
			if (invalid_redirect(temp, STRICT))
				return (true);
		check_heredoc_case(shell, temp);
		if (temp->token_type == TOKEN_OPERATOR)
			if (invalid_operator(temp, STRICT))
				return (true);
		temp = temp->next_token;
	}
	return (false);
}
