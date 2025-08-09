/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:21:22 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/10 00:45:33 by alisharu         ###   ########.fr       */
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

void	append_exit_code(char **res, int code)
{
	char	*tmp;
	char	*num;

	num = ft_itoa(code);
	if (!num)
		return ;
	tmp = ft_strjoin(*res, num);
	free(*res);
	*res = tmp;
	free(num);
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
