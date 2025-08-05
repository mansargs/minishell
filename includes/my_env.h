/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 04:21:43 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/04 04:53:58 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_ENV_H
# define MY_ENV_H

# include "parser.h"
# include <errno.h>

/* Env Helpers */
char				*get_value_data(char *env_line, bool *memprob);
char				*get_key_data(char *env_line);
unsigned int		hash_key(const char *key);

/* Env Operations */
int					env_size(t_env *env);
bool				env_set(t_env *env, char *key, char *value,
						bool has_equal_sign);
void				sort_env_nodes(t_env_node **list, int count);
bool				init_env(t_shell *shell, char **envp);
t_env_node			*env_get(t_env *env, const char *key);
t_env_node			**get_all_env(t_env *env, int *count);

/* Builtin shlvl */
bool				shlvl(t_env *env);

#endif
