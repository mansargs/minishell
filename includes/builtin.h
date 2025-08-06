/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 04:25:25 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/04 23:57:55 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "my_env.h"

/* Export Output */
void	print_sorted_export(t_env *env);

/* Builtins */
int		export_builtin(char **args, t_env *env);
int		unset_builtin(char **arg, t_env *env);
int		env_builtin(char **args, t_env *env);
int		pwd_builtin(char **args, t_env *env);
int		cd_builtin(char **args, t_env *env);
int		echo_builtin(char **args, t_env *env);
int		exit_builtin(t_shell *shell, char **args, bool has_forked);
int		history_builtin(void);
int		count_env_vars(t_env *env);
bool	is_valid_identifier(const char *s);
bool	execute_builtin(char **argv, t_env *env, bool *is_builtin,
			bool has_forked);

#endif
