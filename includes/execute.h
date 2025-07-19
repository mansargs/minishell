/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:50:18 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/19 09:28:01 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "parser.h"
# include <sys/wait.h>

typedef struct s_ast	t_ast;
typedef struct s_env	t_env;

typedef void	(*t_builtin_func)(void);

int		execute_ast(t_ast *node, t_env *env, bool has_forked);
int		execute_command(t_ast *node, t_env *env, bool has_forked);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strcat(char *dest, const char *src);
void	free_matrix(char ***matrix);
char	*join(char *str1, char *str2, char *str3);
int		count_args(t_token *cmd);
char	**convert_env_to_matrix(t_env *env);
bool	execute_builtin(char **argv, t_env *env);
char	*command_search(char **paths);
char	**get_arguments(t_token *cmd_tokens, t_env *env);

#endif
