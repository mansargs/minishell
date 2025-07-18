/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:19:38 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/18 00:20:20 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"


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