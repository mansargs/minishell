/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:28:21 by mansargs          #+#    #+#             */
/*   Updated: 2025/01/23 19:27:05 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t n)
{
	const unsigned char	*buffer;
	unsigned char		c;

	if (n == 0)
		return (NULL);
	c = (unsigned char)value;
	buffer = (const unsigned char *)ptr;
	while (n--)
	{
		if (*buffer == c)
			return ((void *)buffer);
		buffer++;
	}
	return (NULL);
}
