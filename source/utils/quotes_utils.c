/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:21:22 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/11 03:06:18 by mansargs         ###   ########.fr       */
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

void	append_var(t_shell *shell, char **res, const char *str, int *i)
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
	val = get_env_value(shell->envp, name);
	free(name);
	if (val)
		*res = ft_strjoin_free(*res, val);
	else
		*res = ft_strjoin_free(*res, "");
	*i = start + len;
}

char	*remove_dollar_before_quotes(char **str)
{
	char	*result;

	if (!str || !*str)
		return (NULL);
	if ((*str)[0] == '$' && ((*str)[1] == '\"' || (*str)[1] == '\''))
		result = ft_strdup(*str + 1);
	else
		result = ft_strdup(*str);
	if (!result)
		return (NULL);
	free(*str);
	*str = NULL;
	return (result);
}

bool	all_is_quote(const char *line)
{
	if (!line || *line == '\0')
		return (false);
	while (*line)
	{
		if (*line != '\'' && *line != '"')
			return (false);
		++line;
	}
	return (true);
}

bool	process_token(t_env *env, t_token *arg, char **argv, int *i)
{
	bool	only_quotes;

	only_quotes = false;
	if (env->empty_quote_pos == -1 && all_is_quote(arg->token_data))
		only_quotes = true;
	if (handle_quots(env, NULL, arg) == -1)
		return (false);
	if (arg->token_data[0] == '\0' && only_quotes)
		env->empty_quote_pos = *i;
	argv[(*i)] = ft_strdup(arg->token_data);
	return (argv[(*i)++] != NULL);
}
