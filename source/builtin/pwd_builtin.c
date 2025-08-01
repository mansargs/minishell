/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:29:32 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/02 02:53:38 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_builtin_status	pwd_builtin(char **args, t_env *env)
{
	(void)args;
	printf("%s\n", env->shell->pwd);
	env->shell->exit_code = 0;
	return (BUILTIN_OK);
}
