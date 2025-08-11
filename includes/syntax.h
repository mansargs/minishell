/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:24:51 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/11 16:37:52 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# include "token.h"
# include <sys/wait.h>

void	manage_parenthesis(const t_token *token, int *opened_parenthesis);
bool	syntax_and_heredoc(t_shell *shell);
bool	invalid_redirect(const t_token *token, const int strict_flag);
bool	invalid_operator(const t_token *token, const int strict_flag);
bool	strict_syntax_errors(t_shell *shell);
bool	valid_line(t_shell *shell, char **line);
bool	secondary_syntax_errors(const t_token *token, int *opened_parenthesis);
int		handle_quots(t_env *env, char **envp, t_token *token);
char	*open_heredoc(t_shell *shell, const t_token *tokens,
			const int fd_history);
char	*open_quotes_heredoc(t_shell *shell, const char *str, int *open_flag);
char	*open_quotes(t_env *env, char **envp, const char *str, int *open_flag);
void	append_char(char **res, char c);
int		check_is_open_quote(int quote);
char	*get_file_name(void);
void	handle_heredoc_open_quote(t_shell *shell, char *line,
			const int fd);
void	signal_handler(int signum);
void	handle_exitstatus(t_shell *shell);
void	print_error(char *unexpented);
char	*replace_exit_code(t_shell *shell, char *token_str);
void	append_exit_code(char **res, int code);
void	append_var(t_shell *shell, char **res, const char *str, int *i);
char	*remove_dollar_before_quotes(char **str);

#endif
