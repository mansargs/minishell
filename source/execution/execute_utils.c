/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:19:38 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/01 23:06:14 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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
	size_t	len1 = 0;
	size_t	len2 = 0;
	size_t	len3 = 0;
	char	*joined;

	if (str1)
		len1 = ft_strlen(str1);
	if (str2)
		len2 = ft_strlen(str2);
	if (str3)
		len3 = ft_strlen(str3);
	joined = malloc(len1 + len2 + len3 + 1);
	if (!joined)
		return (NULL);
	joined[0] = '\0';
	if (str1)
		ft_strcat(joined, str1);
	if (str2)
		ft_strcat(joined, str2);
	if (str3)
		ft_strcat(joined, str3);
	return (joined);
}
