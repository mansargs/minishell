/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:04:36 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/01 20:56:00 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

char	*open_quotes_heredoc(t_shell *shell, const char *str, int *open_flag)
{
	int		i;
	char	quote;
	char	*res;

	i = 0;
	quote = 0;
	*open_flag = 0;
	res = ft_calloc(1, 1);
	(void)shell;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
		{
			shell->heredoc_quote = 1;
			quote = str[i];
		}
		else if (quote && str[i] == quote)
			quote = 0;
		else
			append_char(&res, str[i]);
		i++;
	}
	if (check_is_open_quote(quote, res) == 0)
		return (NULL);
	return (res);
}

bool	is_quoted_delimiter(const char *s)
{
	size_t	len;

	if (!s)
		return (false);
	len = ft_strlen(s);
	if (len < 2)
		return (false);
	if ((s[0] == '\'' && s[len - 1] == '\'')
		|| (s[0] == '"' && s[len - 1] == '"'))
		return (true);
	return (false);
}
