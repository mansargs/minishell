/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:30:40 by mansargs          #+#    #+#             */
/*   Updated: 2025/01/27 20:31:56 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	size_t	total_len;
	size_t	i;
	int		j;

	i = 0;
	j = -1;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc((total_len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (s1[++j])
		res[i++] = s1[j];
	j = -1;
	while (s2[++j])
		res[i++] = s2[j];
	res[i] = '\0';
	return (res);
}
