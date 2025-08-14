/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:54:15 by alisharu          #+#    #+#             */
/*   Updated: 2025/08/14 15:51:09 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	is_str_greater(const char *str1, const char *str2)
{
	int	len1;
	int	len2;
	int	i;

	i = 0;
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 > len2)
		return (true);
	if (len1 < len2)
		return (false);
	while (i < len1)
	{
		if (str1[i] > str2[i])
			return (true);
		if (str1[i] < str2[i])
			return (false);
		i++;
	}
	return (false);
}

bool	ft_str_is_too_big(const char *str)
{
	int		i;
	bool	negative;

	negative = false;
	i = 0;
	if (!str || str[0] == '\0')
		return (true);
	if (str[0] == '-')
	{
		negative = true;
		i++;
	}
	else if (str[0] == '+')
		i++;
	while (str[i] == '0')
		i++;
	if (str[i] == '\0')
		return (false);
	if (negative)
		if (is_str_greater(&str[i], LONG_MIN_STR))
			return (true);
	if (!negative)
		if (is_str_greater(&str[i], LONG_MAX_STR))
			return (true);
	return (false);
}

bool	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (false);
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (str[i] == '\0')
		return (false);
	while (str[i])
	{
		if (!isdigit((unsigned char)str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	check_exit_argument(t_shell *shell, char **args)
{
	if (!is_numeric(args[1]) || ft_str_is_too_big(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		free_all_data(shell, args);
		exit(2);
	}
}

int	exit_builtin(t_shell *shell, char **args, bool has_forked)
{
	int		exit_code;

	exit_code = 0;
	if (!has_forked)
		ft_putendl_fd("exit", 1);
	if (!args[1])
	{
		free_all_data(shell, args);
		exit(exit_code);
	}
	check_exit_argument(shell, args);
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		shell->my_env->exit_code = 1;
		return (FUNCTION_FAIL);
	}
	exit_code = ft_atol(args[1]);
	free_all_data(shell, args);
	exit(exit_code % 256);
	return (FUNCTION_SUCCESS);
}
