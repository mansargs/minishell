/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:50:18 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/14 16:06:09 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "builtin.h"
# include <dirent.h>
# include <unistd.h>
# include <sys/stat.h>

int		execute_ast(t_ast *node, t_env *env, bool has_forked);
int		execute_command(t_ast *node, t_env *env, bool has_forked);
int		execute_command_no_fork(t_ast *node, t_env *env, bool has_forked);
int		child_execute(char **argv, int cmd_pos, t_env *env);
char	**convert_env_to_matrix(t_env *env);
char	*command_search(char **paths, t_env *env);
char	**get_arguments(t_token *cmd_tokens, t_env *env);
char	*find_command_path(const char *cmd, t_env *env);
bool	add_cmd_to_path(char **paths, const char *cmd);
bool	fill_arguments(t_token *cmd, char **argv, int argc);
bool	open_wildcards(char	***argv);
void	setup_signals(void);
int		handle_child_status(int status, t_env *env);
bool	copy_and_duplicate_old_args(char **new_arg_list, char **old_args);
bool	find_directory_and_word(const char *line, char **dir, char **word);
int		count_lines(char	**lines);
bool	is_match(const char *item_name, const char *pattern);
int		execute_pipe(t_ast *node, t_env *env);
int		open_redirects(t_ast *node, t_shell *shell);
bool	handle_empty_command(char **argv, t_env *env);

#endif
