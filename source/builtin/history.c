/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 02:18:23 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/02 19:33:57 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_execute_status	history_builtin(void)
{
	char			*line;
	unsigned long	count_line;
	int				fd;

	fd = open(".mini_history", O_RDONLY);
	if (fd < 0)
	{
		perror("history doesn't open");
		return (BUILTIN_FAIL);
	}
	count_line = 0;
	while (1)
	{
		++count_line;
		line = get_next_line(fd);
		if (!line)
			return (BUILTIN_FAIL);
		printf("%lu %s", count_line, line);
		free(line);
	}
	if (close(fd) == -1)
		return (perror("close history failed"), BUILTIN_FAIL);
	return (BUILTIN_OK);
}
