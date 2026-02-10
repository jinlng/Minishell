/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:57:37 by potabaga          #+#    #+#             */
/*   Updated: 2026/02/10 19:49:33 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include "libft.h"
# include <signal.h>
# include <fcntl.h>

typedef struct s_env
{
	char	**env;
	int		last_status;
}	t_env;

typedef enum e_redir
{
	REDIR_NONE,
	REDIR_OUT,
	REDIR_APPEND
}	t_redir;

typedef struct s_pipe
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	*path1;
	char	*path2;
	char	**cmd1;
	char	**cmd2;
}	t_pipe;

/* Command Data Structures */

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	int				pipe_out;
	struct s_cmd	*next;
}	t_cmd;

/* Token definitions */

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}	t_token_type;

typedef enum e_quote
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}	t_quote;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	t_quote			quote;
	struct s_token	*next;
}	t_token;

/* Lexer utilities & lexer */
int		is_whitespace(char c);
int		is_operator(char c);
t_token	*new_token(t_token_type type, char *value, t_quote quote);
void	token_add_back(t_token **lst, t_token *new);
t_token	*lexer(char *input);
void	*create_operator_token(t_token **tokens, char *input, int *i);
char	*extract_word(char *s, int *i, t_quote *quote);


char	*find_cmd(char *cmd);
void	builtin_pwd(t_env *env);
void	builtin_echo(char **args, t_env *env);
void	builtin_cd(char **args, t_env *env);
void	builtin_env(t_env *env);
void	builtin_export(char **args, t_env *env);
void	builtin_exit(char **args, t_env *env);
void	builtin_echo_with_redir(char **args, t_env *env);
void	free_args(char **args);
char	**parse_line(char *line);
void	execute_cmd(char **args, t_env *env);
void	process_line(char *line, t_env *env);
int		has_redir(char **args);
void	free_args(char **args);
char	*get_cmd_path(char *cmd);
void	handle_sigint(int sig);
void	set_parent_signals(void);
void	set_child_signals(void);
void	init_env(t_env *env, char **envp);
int		env_index(t_env *env, char *name);
void	env_set(t_env *env, char *args);
int		is_valid_identifier(char *s);
int		apply_redir(char **args);
int		has_append(char **args);
int		has_input(char **args);
int		apply_input_redir(char **args);
void	restore_stdin(int save_stdin);
int		arr_len(char **arr);
int		has_pipe(char **args);
void	execute_pipe(char **args, t_env *env);
void	execute_pipeline(char **args);
char	**copy_args(char **args, int start, int end);
int		init_pipe(t_pipe *p, char **args);
char	**get_cmd_part(char **args, int start, int end);
int		get_pipe_paths(char **cmd1, char **cmd2, char **path1, char **path2);
void	exec_pipe_left(int *fd, char *path, char **cmd, t_env *env);
void	exec_pipe_right(int *fd, char *path, char **cmd, t_env *env);

#endif
