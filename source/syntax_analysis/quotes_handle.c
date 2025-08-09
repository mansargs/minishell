/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:40:43 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/10 00:22:05 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static int	handle_quotes(const char *str, int *i, char *quote)
{
	if (!*quote && (str[*i] == '\'' || str[*i] == '"'))
	{
		*quote = str[*i];
		(*i)++;
		return (1);
	}
	if (*quote && str[*i] == *quote)
	{
		*quote = 0;
		(*i)++;
		return (1);
	}
	return (0);
}

static int	handle_dollar(t_env *env, char **envp, const char *str,
	char **res, int *i, char quote)
{
	if (str[*i] == '$' && quote != '\'')
	{
		if (str[*i + 1] && str[*i + 1] == '?')
		{
			append_exit_code(res, env->exit_code);
			(*i) += 2;
		}
		else
			append_var(res, envp, str, i);
		return (1);
	}
	return (0);
}

int	parser_quote_loop(t_env *env, char **envp, const char *str,
	char **res, char *quote)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (handle_quotes(str, &i, quote))
			continue ;
		if (handle_dollar(env, envp, str, res, &i, *quote))
			continue ;
		append_char(res, str[i]);
		i++;
		if (!*res)
			return (0);
	}
	return (1);
}
//

char	*open_quotes(t_env *env, char **envp, const char *str, int *open_flag)
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
	if (!parser_quote_loop(env, envp, str, &res, &quote))
		return (free(res), NULL);
	if (check_is_open_quote(quote) == 0)
		return (free(res), NULL);
	return (res);
}

int	handle_quots(t_env *env, char **envp, t_token *token)
{
	char	*str;
	int		open_flag;

	open_flag = 0;
	str = remove_dollar_before_quotes(&token->token_data);
	if (!str)
		return (-1);
	token->token_data = str;
	str = open_quotes(env, envp, token->token_data, &open_flag);
	if (!str)
		return (-1);
	free(token->token_data);
	token->token_data = str;
	return (0);
}
