/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:30:45 by mansargs          #+#    #+#             */
/*   Updated: 2025/01/26 14:15:56 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dst_len;

	i = 0;
	j = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	i = dst_len;
	if (dst_len >= dstsize)
		return (src_len + dstsize);
	while (src[j] && (i < dstsize - 1))
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (src_len + dst_len);
}
