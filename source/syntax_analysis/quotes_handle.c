/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:40:43 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/10 00:55:54 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static int	handle_quotes(t_parser_data *data)
{
	if (!data->quote && (data->str[data->i] == '\''
			|| data->str[data->i] == '"'))
	{
		data->quote = data->str[data->i];
		data->i++;
		return (1);
	}
	if (data->quote && data->str[data->i] == data->quote)
	{
		data->quote = 0;
		data->i++;
		return (1);
	}
	return (0);
}

static int	handle_dollar(t_shell *shell, t_parser_data *data)
{
	if (data->str[data->i] == '$' && data->quote != '\'')
	{
		if (data->str[data->i + 1] && data->str[data->i + 1] == '?')
		{
			append_exit_code(data->res, data->env->exit_code);
			data->i += 2;
		}
		else
			append_var(shell, data->res, data->str, &(data->i));
		return (1);
	}
	return (0);
}

int	parser_quote_loop(t_shell *shell, t_parser_data *data)
{
	while (data->str[data->i])
	{
		if (handle_quotes(data))
			continue ;
		if (handle_dollar(shell, data))
			continue ;
		append_char(data->res, data->str[data->i]);
		data->i++;
		if (!*data->res)
			return (0);
	}
	return (1);
}


char	*open_quotes(t_env *env, char **envp, const char *str, int *open_flag)
{
	t_parser_data	data;
	char			*res;

	if (!str)
		return (NULL);
	data.env = env;
	data.envp = envp;
	data.str = str;
	data.quote = 0;
	data.i = 0;
	*open_flag = 0;
	res = ft_calloc(1, 1);
	if (!res)
		return (NULL);
	data.res = &res;
	if (!parser_quote_loop(env->shell, &data))
		return (free(res), NULL);
	if (check_is_open_quote(data.quote) == 0)
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
