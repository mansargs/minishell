/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:48:49 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/21 18:14:20 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

size_t	ft_gnl_strlen(const char *str);
char	*ft_gnl_strchr(const char *str, int c);
char	*ft_gnl_strjoin(char *s1, const char *s2);
char	*ft_gnl_substr(const char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
void	clear(char **line);

#endif
