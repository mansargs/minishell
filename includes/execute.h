/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:50:18 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/02 03:03:26 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "parser.h"
# include <dirent.h>

typedef struct s_ast	t_ast;
typedef struct s_env	t_env;

int					execute_ast(t_ast *node, t_env *env, bool has_forked);
int					execute_command(t_ast *node, t_env *env, bool has_forked);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strcat(char *dest, const char *src);
void				free_matrix(char ***matrix);
char				*join(char *str1, char *str2, char *str3);
int					count_args(t_token *cmd);
char				**convert_env_to_matrix(t_env *env);
char				*command_search(char **paths, t_env *env);
char				**get_arguments(t_token *cmd_tokens, t_env *env);
char				*find_command_path(const char *cmd, t_env *env);
bool				add_cmd_to_path(char **paths, const char *cmd);
bool				fill_arguments(t_token *cmd, char **argv, int argc);
void				free_ast(t_ast *tree);
bool				open_wildcards(char	***argv);

void				setup_signals();

#endif
