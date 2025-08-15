/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:18:03 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/15 16:44:11 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static char	*build_new_token(const char *before, const char *exit_code_str,
	const char *after)
{
	char	*new_token;

	new_token = ft_calloc(ft_strlen(before) + ft_strlen(exit_code_str)
			+ ft_strlen(after) + 1, sizeof(char));
	if (!new_token)
		return (NULL);
	ft_strcpy(new_token, before);
	ft_strcat(new_token, exit_code_str);
	ft_strcat(new_token, after);
	return (new_token);
}

char	*replace_exit_code(t_shell *shell, char *token_str)
{
	char	*pos;
	char	*before;
	char	*after;
	char	*exit_code_str;
	char	*new_token;

	pos = ft_strnstr(token_str, "$?", ft_strlen(token_str));
	if (!pos)
		return (NULL);
	exit_code_str = ft_itoa(shell->my_env->exit_code);
	if (!exit_code_str)
		return (NULL);
	before = ft_strndup(token_str, pos - token_str);
	after = ft_strdup(pos + 2);
	if (!before || !after)
		return (free(exit_code_str), free(before), free(after), NULL);
	new_token = build_new_token(before, exit_code_str, after);
	free(exit_code_str);
	free(before);
	free(after);
	return (new_token);
}

void	open_exitstatus(t_shell *shell, t_token *token)
{
	char	*new_token;

	new_token = replace_exit_code(shell, token->token_data);
	if (!new_token)
		return ;
	free(token->token_data);
	token->token_data = new_token;
}

static bool	is_exitstatus(t_token *token, bool *exitstatus_flag)
{
	const t_token	*temp;

	temp = token;
	while (temp)
	{
		if (temp->token_type == TOKEN_WORD
			&& ft_strnstr(temp->token_data, "$?", ft_strlen(temp->token_data)))
		{
			*exitstatus_flag = true;
			return (true);
		}
		temp = temp->next_token;
	}
	return (false);
}

void	handle_exitstatus(t_shell *shell)
{
	t_token	*cur;

	if (!is_exitstatus(shell->tokens, &shell->history.exitstatus_flag))
		return ;
	cur = shell->tokens;
	while (cur)
	{
		if (cur->token_type == TOKEN_WORD
			&& ft_strnstr(cur->token_data, "$?", ft_strlen(cur->token_data)))
			open_exitstatus(shell, cur);
		cur = cur->next_token;
	}
}
