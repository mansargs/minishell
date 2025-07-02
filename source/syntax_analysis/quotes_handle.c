/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:40:43 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/02 14:59:36 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

char	*strip_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*result;

	j = 0;
	i = 0;
	quote = 0;
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote = str[i++];
		else if (quote && str[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
			result[j++] = str[i++];
	}
	if (quote)
		return (free(result),
			printf("minishell: syntax error: unclosed quote\n"), NULL);
	result[j] = '\0';
	return (result);
}

int	handle_quoted(t_token *token)
{
	char	*str;

	str = strip_quotes(token->token_data);
	if (!str)
		return (-1);
	printf("%s\n", str);
	free(str);
	return (0);
}
