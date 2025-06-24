/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:50:59 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/24 13:21:46 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

bool	first_is_operator(t_token *head)
{
	if (!head)
		return (false);
	if (head->token_type == TOKEN_OPERATOR
		&& head->token_operator_type != OPERATOR_PAREN_OPEN)
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
			head->token_data);
		return (true);
	}
	return (false);
}

bool	operator_after_operator(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp->next_token)
	{
		if (tmp->token_type == TOKEN_OPERATOR
			&& tmp->next_token->token_type == TOKEN_OPERATOR
			&& tmp->next_token->token_operator_type != OPERATOR_PAREN_OPEN
			&& tmp->next_token->token_operator_type != OPERATOR_PAREN_CLOSE)
		{
			printf("minishell: syntax error near unexpected token `%s'\n",
				tmp->next_token->token_data);
			return (true);
		}
		tmp = tmp->next_token;
	}
	return (false);
}

bool	operator_after_redirection(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp->next_token)
	{
		if (tmp->token_type == TOKEN_REDIRECT
			&& tmp->next_token->token_type == TOKEN_OPERATOR)
		{
			printf("minishell: syntax error near unexpected token `%s'\n",
				tmp->next_token->token_data);
			return (true);
		}
		tmp = tmp->next_token;
	}
	return (false);
}

bool	operator_after_open_paren(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp && tmp->next_token)
	{
		if (tmp->token_operator_type == OPERATOR_PAREN_OPEN)
		{
			if (tmp->next_token->token_type == TOKEN_OPERATOR)
			{
				if (tmp->next_token->token_operator_type != OPERATOR_PAREN_OPEN
					&& tmp->next_token->token_operator_type
					!= OPERATOR_PAREN_CLOSE)
				{
					printf("minishell: syntax error near unexpected token `%s'\n",
						tmp->next_token->token_data);
					return (true);
				}
			}
		}
		tmp = tmp->next_token;
	}
	return (false);
}

bool	operator_before_close_paren(t_token *head)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = head;
	prev = NULL;
	while (tmp)
	{
		if (tmp->token_operator_type == OPERATOR_PAREN_CLOSE)
		{
			if (!prev || (prev->token_type == TOKEN_OPERATOR
					&& prev->token_operator_type != OPERATOR_PAREN_CLOSE))
			{
				printf("minishell: syntax error near unexpected token `)'\n");
				return (true);
			}
		}
		prev = tmp;
		tmp = tmp->next_token;
	}
	return (false);
}
