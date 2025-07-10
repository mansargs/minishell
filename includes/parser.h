/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisharu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:22:46 by mansargs          #+#    #+#             */
/*   Updated: 2025/07/10 21:52:16 by alisharu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "syntax.h"
# define HASH_SIZE 128

typedef struct s_ast
{
	t_token			*tokens;
	struct s_ast	*left_side;
	struct s_ast	*right_side;
	t_list			*cmd;
	t_list			*redir;
}	t_ast;

typedef struct s_env_node
{
	int					is_equal;
	char				*key;
	char				*value;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_env
{
	t_env_node	*env[HASH_SIZE];
}	t_env;


t_ast			*building_ast(t_token	*head);
t_env			*init_env(char **envp);
bool			logic_division(t_ast **branch, t_token *head);
bool			command_redirection_division(t_ast *branch);
bool			division_into_parenthesis(t_ast **branch, t_token *head);
void			free_env_table(t_env *env);
void			env_set(t_env *env, char *key, char *value, int is_equal);
char			*get_value_data(char *env_line);
char			*get_key_data(char *env_line);
unsigned int	hash_key(const char *key);

void			free_string_array(char **arr);
char			**token_list_to_array(t_token *token);
void			handle_builtin_commands(t_shell *shell, t_env *env);
int				is_valid_identifier(const char *str);
void			free_env_table(t_env *env);
void			handle_export_argument(char *arg, t_env *env);
void			print_sorted_export(t_env *env);
int				export_builtin(char **args, t_env *env);
t_env_node		**gather_all_env(t_env *env, int *count);

#endif
