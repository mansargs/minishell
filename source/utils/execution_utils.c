/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 04:04:48 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/04 04:04:55 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	add_cmd_to_path(char **paths, const char *cmd)
{
	int		i;
	char	*temp;
	char	*joined;

	if (!cmd)
		return (false);
	temp = ft_strjoin("/", cmd);
	if (!temp)
		return (false);
	i = -1;
	while (paths[++i])
	{
		joined = ft_strjoin(paths[i], temp);
		if (!joined)
			return (free(temp), false);
		free(paths[i]);
		paths[i] = joined;
	}
	free(temp);
	return (true);
}

int	count_args(t_token *cmd)
{
	const t_token	*temp;
	int				count;

	count = 1;
	temp = cmd->next_token;
	while (temp)
	{
		++count;
		temp = temp->next_token;
	}
	return (count);
}

char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	if (!dst || !src)
		return (NULL);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (!dest || !src)
		return (NULL);
	while (dest[i])
		i++;
	while (src[j])
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (dest);
}

char	*join(char *str1, char *str2, char *str3)
{
	char	*joined;
	size_t	len;

	if (!str1 || !str2 || !str3)
		return (NULL);
	len = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3) + 1;
	joined = ft_calloc(len, sizeof(char));
	if (!joined)
		return (NULL);
	ft_strcpy(joined, str1);
	ft_strcat(joined, str2);
	ft_strcat(joined, str3);
	return (joined);
}
