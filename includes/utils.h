/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 02:53:22 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/11 02:56:28 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"

/* Free functions */
void	free_matrix(char ***matrix);
void	free_ast(t_ast **tree);
void	free_env_table(t_env *env);
void	free_shell(t_shell **shell);
void	conditional_free(t_shell **shell, bool ast, bool minishell);
void	free_tokens(t_token **tokens);
void	free_token(t_token **token);
char	*ft_strjoin_free(char *s1, const char *s2);

/* Environement */

int		is_env_char(char c);
char	*get_env_value(char **envp, const char *str);
int		count_env_vars(t_env *env);
void	print_export_error(t_env *env, char *key);

/* Execution */

bool	add_cmd_to_path(char **paths, const char *cmd);
int		count_args(t_token *cmd);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strcat(char *dest, const char *src);
char	*join(char *str1, char *str2, char *str3);

/* Tokens */

t_token	*add_token(t_token **head, t_token *new_token);
t_token	*last_token(t_token *head);
int		count_tokens(t_token *token);
bool	only_spaces(const char *str);
bool	is_space(char tok);
bool	is_redirect(char tok);
bool	is_special_char(char tok);
bool	is_special_operator(char tok);
int		skip_variable(const char *line, int i);

/* Libs */
char	*ft_strndup(const char *s, size_t n);

/* Builtins */

char	*handle_cd_without_dir(char **args, t_env *env);
int		check_too_many_dirs(char **args, t_env *env);
void	failed_chdir(t_env *env, char *path);

bool	all_is_quote(const char *line);
bool	process_token(t_env *env, t_token *arg, char **argv, int *i);

#endif
