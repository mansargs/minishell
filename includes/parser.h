/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:22:46 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/02 19:33:57 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "syntax.h"
# include "execute.h"

# define PATH_MAX 4096
# define ENV_TABLE_SIZE 128
# define LONG_MAX_STR "9223372036854775807"
# define LONG_MIN_STR "9223372036854775808"

/* AST */
t_ast			*building_ast(t_token *head);
bool			logic_division(t_ast **branch, t_token *head);
bool			command_redirection_division(t_ast *branch);
bool			division_into_parenthesis(t_ast *branch);

/* Env Helpers */
char			*get_value_data(char *env_line, bool *memprob);
char			*get_key_data(char *env_line);
unsigned int	hash_key(const char *key);

/* Freeing */
void			free_array(char **arr);
void			free_env_table(t_env *env);

/* Env Operations */
int				env_size(t_env *env);
bool			env_set(t_env *env, char *key, char *value, bool has_equal_sign);
void			sort_env_nodes(t_env_node **list, int count);
bool			init_env(t_shell *shell, char **envp);
t_env_node		*env_get(t_env *env, const char *key);
t_env_node		**get_all_env(t_env *env, int *count);

/* Export Output */
void			print_sorted_export(t_env *env);

/* Builtins */

t_execute_status	export_builtin(char **args, t_env *env);
t_execute_status	unset_builtin(char **arg, t_env *env);
t_execute_status	env_builtin(char **args, t_env *env);
t_execute_status	pwd_builtin(char **args, t_env *env);
t_execute_status	cd_builtin(char **args, t_env *env);
t_execute_status	echo_builtin(char **args, t_env *env);
t_execute_status	exit_builtin(t_shell *shell, char **args);
t_execute_status	history_builtin(void);
t_execute_status	execute_builtin(char **argv, t_env *env);
int					count_env_vars(t_env *env);
void				handle_builtin_commands(t_shell *shell, t_env *env);
bool				is_valid_identifier(const char *s);

#endif
