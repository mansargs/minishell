/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:32:16 by mansargs          #+#    #+#             */
/*   Updated: 2025/01/23 19:28:57 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char			*last;
	unsigned char	search_char;

	last = NULL;
	search_char = (unsigned char)c;
	if (search_char == '\0')
		return ((char *)str + ft_strlen(str));
	while (*str != '\0')
	{
		if (*str == search_char)
			last = (char *)str;
		++str;
	}
	return (last);
}
