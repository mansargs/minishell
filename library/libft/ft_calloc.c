/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:24:21 by mansargs          #+#    #+#             */
/*   Updated: 2025/01/26 14:28:07 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*mem;
	size_t			i;

	mem = (unsigned char *)malloc(count * size);
	i = 0;
	if (!mem)
		return (NULL);
	while (i < count * size)
	{
		*(mem + i) = 0;
		++i;
	}
	return ((void *)mem);
}
