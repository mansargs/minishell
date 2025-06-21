/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:28:29 by mansargs          #+#    #+#             */
/*   Updated: 2025/01/27 20:47:10 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *source, size_t n)
{
	unsigned char	*dst;
	unsigned char	*src;
	size_t			i;

	if (!source && !dest)
		return (dest);
	i = 0;
	dst = (unsigned char *)dest;
	src = (unsigned char *)source;
	while (i < n)
	{
		*(dst + i) = *(src + i);
		++i;
	}
	return (dest);
}
