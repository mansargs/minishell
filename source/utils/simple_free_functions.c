/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_free_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 03:45:26 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/15 03:04:36 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

void	free_matrix(char ***matrix)
{
	int	i;

	if (!matrix || !*matrix)
		return ;
	i = 0;
	while ((*matrix)[i])
	{
		free((*matrix)[i]);
		i++;
	}
	free(*matrix);
	*matrix = NULL;
}

void	free_tokens(t_token **tokens)
{
	t_token	*curr;
	t_token	*next;

	if (!tokens || !*tokens)
		return ;
	curr = *tokens;
	while (curr)
	{
		next = curr->next_token;
		free_token(&curr);
		curr = next;
	}
	*tokens = NULL;
}

void	free_token(t_token **token)
{
	if (!token || !*token)
		return ;
	if ((*token)->token_data)
	{
		free((*token)->token_data);
		(*token)->token_data = NULL;
	}
	if ((*token)->file_name)
	{
		if ((*token)->token_redirect_type == REDIRECT_HEREDOC)
			unlink((*token)->file_name);
		free((*token)->file_name);
		(*token)->file_name = NULL;
	}
	free(*token);
	*token = NULL;
}

void	free_if_execve_fail(char **argv, int cmd_pos, char *cmd_path,
		char **envp)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(argv[cmd_pos], STDERR_FILENO);
	perror("");
	free(cmd_path);
	free_matrix(&envp);
}
