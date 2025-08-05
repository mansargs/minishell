/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:53:47 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/05 13:37:27 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	print_arg_with_exitcode(char *arg, int *exit_code)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] == '?')
		{
			printf("%d", *exit_code);
			i += 2;
		}
		else
		{
			printf("%c", arg[i]);
			i++;
		}
	}
}

int	echo_builtin(char **args, t_env *env)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		newline = false;
		i++;
	}
	while (args[i])
	{
		print_arg_with_exitcode(args[i], &env->shell->exit_code);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	env->shell->exit_code = 0;
	return (FUNCTION_SUCCESS);
}
