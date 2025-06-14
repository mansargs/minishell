/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:11:21 by alisharu          #+#    #+#             */
/*   Updated: 2025/06/14 21:05:50 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H


# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "token_type.h"

typedef struct s_token
{
	char			*token_data;
	t_token_type	token_type;
	t_token_class	token_class;
	struct s_token	*next_token;
}	t_token;


#endif