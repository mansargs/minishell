/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:54:15 by alisharu          #+#    #+#             */
/*   Updated: 2025/07/18 20:58:03 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// if (ft_str_is_too_big(args[1]))
// {
// 	ft_putstr_fd("minishell: exit: ", 2);
// 	ft_putstr_fd(args[1], 2);
// 	ft_putendl_fd(": numeric argument required", 2);
// 	exit(255);
// }


// void	exit_builtin(t_shell *shell, char **args)
// {
// 	long	exit_code;

// 	exit_code = 0;
// 	if (!args[1])
// 		return (shell->exit_code);
// 	if (args[2])
// 	{
// 		ft_putendl_fd("minishell: exit: too many arguments", 2);
// 		shell->exit_code = 1;
// 		return ;
// 	}
// 	if (!is_numeric(args[1]))
// 	{
// 		ft_putstr_fd("minishell: exit: ", 2);
// 		ft_putstr_fd(args, 2);
// 		ft_putendl_fd(": numeric argument required", 2);
// 		exit(2);
// 	}
// 	if (ft_str_is_too_big(args[1]))
// 	{
// 		ft_putstr_fd("minishell: exit: ", 2);
// 		ft_putstr_fd(args[1], 2);
// 		ft_putendl_fd(": numeric argument required", 2);
// 		exit(255);
// 	}
// 	if (ft_atol(args[1]) > 256)
// 	{
// 		exit_code = ft_atol(args[1]);
// 		return (exit_code % 256);
// 	}
// }
