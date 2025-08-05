/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 02:14:36 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/04 05:01:31 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

char	*get_user_part(t_shell *shell)
{
	char	*user_name;
	char	*tmp;
	char	*head;
	bool	is_tmp_user;

	user_name = get_env_value(shell->envp, "USER");
	if (!user_name)
	{
		user_name = ft_strdup("unknown");
		is_tmp_user = true;
	}
	else
		is_tmp_user = false;
	tmp = ft_strjoin("minishell@", user_name);
	if (is_tmp_user)
		free(user_name);
	head = ft_strjoin(tmp, ":");
	free(tmp);
	tmp = ft_strjoin(COLOR_BLUE, head);
	free(head);
	head = ft_strjoin(tmp, COLOR_RESET);
	free(tmp);
	return (head);
}

char	*get_path_and_dollar_part(t_shell *shell)
{
	char	*tmp;
	char	*body;
	char	*dollar;
	char	*prompt;

	tmp = ft_strjoin(COLOR_BRIGHT_PURPLE, shell->pwd);
	body = ft_strjoin(tmp, COLOR_RESET);
	free(tmp);
	tmp = ft_strjoin(COLOR_BRIGHT_PURPLE, "$ ");
	dollar = ft_strjoin(tmp, COLOR_RESET);
	free(tmp);
	tmp = ft_strjoin(body, dollar);
	free(body);
	free(dollar);
	prompt = tmp;
	return (prompt);
}

char	*ps_path(t_shell *shell)
{
	char	*head;
	char	*tail;
	char	*prompt;

	head = get_user_part(shell);
	tail = get_path_and_dollar_part(shell);
	prompt = ft_strjoin(head, tail);
	free(head);
	free(tail);
	return (prompt);
}
