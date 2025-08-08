/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 03:11:37 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/08 21:37:12 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include "macros.h"
# include "../library/libft/libft.h"

/* Tokens individual info */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_OPERATOR,
	TOKEN_PAREN,
	TOKEN_REDIRECT
}	t_token_type;

typedef enum e_operator_type
{
	OPERATOR_NONE,
	OPERATOR_PIPE,
	OPERATOR_OR,
	OPERATOR_AND
}	t_operator_type;

typedef enum e_redirection_type
{
	REDIRECT_NONE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	REDIRECT_HEREDOC
}	t_redirection_type;

typedef enum e_paren_type
{
	PAREN_NONE,
	PAREN_OPEN,
	PAREN_CLOSE
}	t_paren_type;

typedef struct s_token
{
	char				*token_data;
	char				*file_name;
	t_token_type		token_type;
	t_operator_type		token_operator_type;
	t_redirection_type	token_redirect_type;
	t_paren_type		token_paren_type;
	struct s_token		*next_token;
	struct s_token		*prev_token;
}	t_token;

/* Environement abstraction */

typedef struct s_shell	t_shell;

typedef struct s_env_flags
{
	bool	has_equal_sign;
	bool	mem_error;
}	t_env_flags;

typedef struct s_env_node
{
	bool				has_equal_sign;
	char				*key;
	char				*value;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_env
{
	t_env_node	*env[HASH_SIZE];
	t_shell		*shell;
	bool		is_builtin;
}	t_env;

/* Abstract Syntax Tree struct */

typedef struct s_ast
{
	t_token			*tokens;
	struct s_ast	*left_side;
	struct s_ast	*right_side;
	t_token			*cmd;
	t_token			*redir;
}	t_ast;

/* Main shell disagn*/

typedef struct s_history
{
	int		fd;
	bool	is_there_heredoc;
	bool	exitstatus_flag;
}				t_history;

typedef struct s_shell
{
	bool		mem_error;
	int			heredoc_quote;
	int			exit_code_flag;
	int			exit_code;
	char		*pwd;
	char		**envp;
	t_history	history;
	t_token		*tokens;
	t_ast		*tree;
	t_env		*my_env;
	bool		interactive_mode;
}	t_shell;

#endif
