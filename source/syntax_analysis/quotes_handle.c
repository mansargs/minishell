/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:40:43 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/03 20:01:00 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

void	append_char(char **res, char c)
{
	char	tmp[2];
	char	*new;

	if (!*res)
		return ;
	tmp[0] = c;
	tmp[1] = '\0';
	new = ft_strjoin(*res, tmp);
	if (!new)
	{
		free(*res);
		*res = NULL;
		return ;
	}
	free(*res);
	*res = new;
}

void	append_var(char **res, char **envp, const char *str, int *i)
{
	int		start;
	int		len;
	char	*name;
	char	*val;

	start = *i + 1;
	len = 0;
	while (is_env_char(str[start + len]))
		len++;
	if (len == 0)
	{
		append_char(res, str[*i]);
		(*i)++;
		return ;
	}
	name = ft_substr(str, start, len);
	val = get_env_value(envp, name);
	free(name);
	if (val)
		*res = ft_strjoin_free(*res, val);
	else
		*res = ft_strjoin_free(*res, "");
	*i = start + len;
}

static int	parser_quote_loop(char **envp, const char *str,
	char **res, char *quote)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!*quote && (str[i] == '\'' || str[i] == '"'))
			*quote = str[i++];
		else if (*quote && str[i] == *quote)
		{
			*quote = 0;
			i++;
		}
		else if (str[i] == '$' && *quote != '\'')
			append_var(res, envp, str, &i);
		else
			append_char(res, str[i++]);
		if (!*res)
			return (0);
	}
	return (1);
}

char	*open_quotes(char **envp, const char *str, int *open_flag)
{
	char	quote;
	char	*res;

	if (!str)
		return (NULL);
	quote = 0;
	*open_flag = 0;
	res = ft_calloc(1, 1);
	if (!res)
		return (NULL);
	if (!parser_quote_loop(envp, str, &res, &quote))
	{
		free(res);
		return (NULL);
	}
	if (check_is_open_quote(quote) == 0)
	{
		free(res);
		return (NULL);
	}
	return (res);
}

int	handle_quots(char **envp, t_token *token)
{
	char	*str;
	int		open_flag;

	open_flag = 0;
	str = open_quotes(envp, token->token_data, &open_flag);
	if (!str)
		return (-1);
	free(token->token_data);
	token->token_data = str;
	return (0);
}
