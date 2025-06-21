/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:29:57 by mansargs          #+#    #+#             */
/*   Updated: 2025/01/23 18:06:58 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	search_char;

	search_char = (unsigned char)c;
	if (search_char == '\0')
		return ((char *)str + ft_strlen(str));
	while (*str != '\0')
	{
		if (*str == search_char)
			return ((char *)str);
		++str;
	}
	return (NULL);
}
