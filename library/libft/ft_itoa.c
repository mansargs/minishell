/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:28:05 by mansargs          #+#    #+#             */
/*   Updated: 2025/01/26 16:02:31 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_char(int num)
{
	size_t	len;

	len = 1;
	if (num < 0)
		++len;
	while (num / 10)
	{
		num /= 10;
		++len;
	}
	return (len);
}

static int	minus_case(char *str, int *len, int *num)
{
	int	limit;

	limit = 0;
	if (*num < 0)
	{
		*str = '-';
		limit = 1;
		if (*num == -2147483648)
		{
			*num = (*num + 1) * -1;
			*(str + --(*len)) = '8';
			*num /= 10;
		}
		else
			*num *= -1;
	}
	return (limit);
}

char	*ft_itoa(int num)
{
	int		len;
	char	*str;
	int		limit;

	len = count_char(num);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	*(str + len) = '\0';
	limit = minus_case(str, &len, &num);
	while (len > limit)
	{
		*(str + len - 1) = (num % 10) + '0';
		num = num / 10;
		--len;
	}
	return (str);
}
