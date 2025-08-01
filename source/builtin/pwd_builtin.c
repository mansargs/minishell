/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:29:32 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/01 12:17:35 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	pwd_builtin(char **args, t_env *env)
{
	(void)args;
	printf("%s\n", env->shell->pwd);
	env->shell->exit_code = 0;
	return (true);
}
