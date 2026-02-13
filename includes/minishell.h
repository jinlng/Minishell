/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:57:37 by potabaga          #+#    #+#             */
/*   Updated: 2026/02/13 19:06:20 by jinliang         ###   ########.fr       */
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

/* ONLY ONE global variable */
extern int	g_exit_status;

typedef struct s_env
{
	char	**env;
	int		last_status;
	char			*key;
	char			*value;
	int				exported;
	struct s_env	*next;
}	t_env;

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

/* Token definitions */
typedef enum	e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}	t_token_type;

typedef enum	e_quote
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}	t_quote;

/* Token structure */
typedef struct	s_token
{
	t_token_type	type;
	char			*value;
	t_quote			quote;
	struct s_token	*next;
}	t_token;

/* Redir structure */
typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	t_quote			quote;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

/* Command Data Structures */
typedef struct	s_cmd
{
	char			**argv;
	t_token			*token;
	t_redir			*redir;
	int				pipe_out;
	struct s_cmd	*next;
}	t_cmd;

/* builtin type structure */
typedef struct s_builtin
{
	char	*name;
	int		(*func)(char **argv, t_env **env);
}	t_builtin;

/* Lexer utilities & lexer */
int		is_whitespace(char c);
int		is_operator(char c);
t_token	*new_token(t_token_type type, char *value, t_quote quote);
void	token_add_back(t_token **lst, t_token *new);
t_token	*lexer(char *input);
void	*create_operator_token(t_token **tokens, char *input, int *i);
char	*extract_word(char *s, int *i, t_quote *quote);
char	*build_word_without_quotes(char *src, int len, t_quote quote);

/* expansion tools & expansion */
int		is_var_char(char c);
char	*get_env_value(char *name, t_env *env);
int		get_var_name_len(char *str);

char	*expand_str(char *str, t_env *env);
void	expand_tokens(t_token *tok, t_env *env);

/* parser tools & parser */
t_cmd	*init_cmd(void);
// void	add_redir(t_cmd *cmd, t_token *tok);
void	add_arg(t_cmd *cmd, char *arg);
void	add_redir(t_cmd *cmd, t_token_type type, char *file, t_quote quote);
t_cmd	*parser(t_token *tok);
void	handle_word(t_cmd *cur, t_token *tok);
int		handle_pipe(t_cmd **cur);
int		handle_redir(t_cmd *cur, t_token **tok);



/* builtin functions */
int	builtin_echo(char **argv, t_env **env);
int	builtin_cd(char **argv, t_env **env);
int	builtin_pwd(char **argv, t_env **env);
int	builtin_export(char **argv, t_env **env);
int	builtin_unset(char **argv, t_env **env);
int	builtin_env(char **argv, t_env **env);
int	builtin_exit(char **argv, t_env **env);

/* builtin dispatcher */
int		is_builtin(t_cmd *cmd);
int		exec_builtin(t_cmd *cmd, t_env **env);


/* signal */
void	sigint_handler(int sig);
void	handle_sigint_in_heredoc(int sig);
void	sigint_heredoc(int sig);

int		process_heredocs(t_cmd *cmd);
int		prepare_heredoc(t_redir *r);
void	heredoc_child(int fd[2], t_redir *r);


/* exacution */
void	execute(t_cmd *cmd, t_env *env);
void	exec_child(t_cmd *cmd, t_env *env, int prev_fd, int pipe_fd[2]);
void	exec_parent(t_cmd *cmd, int *prev_fd, int pipe_fd[2], pid_t pid);
void	setup_redirections(t_cmd *cmd);
void	exec_external(t_cmd *cmd, t_env *env);
void	wait_all(void);

int	create_pipe_if_needed(t_cmd *cmd, int pipe_fd[2]);


/* helper functions */
int	is_valid_identifier(char *s);
int is_numeric(char *s);
/* Debug Printer */
void print_tokens(t_token *tok);
void print_cmds(t_cmd *cmd);


/* env */
void	init_env(t_env *env, char **envp);
int		env_index(t_env *env, char *name);
void	env_set(t_env **env, char *arg);
int		env_size(t_env *env);
char	**convert_env_to_array(t_env *env);

/* path */
char	*get_cmd_path(char *cmd, t_env *env);
char	**convert_env_to_array(t_env *env);



/* free related */
void	free_tokens(t_token *tok);
void	free_redir(t_redir *redir);
void	free_cmd(t_cmd *cmd);
void	free_env(t_env *env);
void	free_split(char **arr);
void	free_envp(char **envp);
void	free_all_global(t_env *env);

/* error */
int	error_msg(char *msg);
int	perror_msg(char *prefix, char *arg);
















// char	*find_cmd(char *cmd);
// void	builtin_pwd(t_env *env);
// void	builtin_echo(char **args, t_env *env);
// void	builtin_cd(char **args, t_env *env);
// void	builtin_env(t_env *env);
// void	builtin_export(char **args, t_env *env);
// void	builtin_exit(char **args, t_env *env);
// void	builtin_echo_with_redir(char **args, t_env *env);
// void	free_args(char **args);
// // char	**parse_line(char *line);
// void	execute_cmd(char **args, t_env *env);
// void	process_line(char *line, t_env *env);
// int		has_redir(char **args);
// void	free_args(char **args);
// char	*get_cmd_path(char *cmd);
// void	handle_sigint(int sig);
// void	set_parent_signals(void);
// void	set_child_signals(void);
// void	init_env(t_env *env, char **envp);
// int		env_index(t_env *env, char *name);
// void	env_set(t_env *env, char *args);
// int		is_valid_identifier(char *s);
// int		apply_redir(char **args);
// int		has_append(char **args);
// int		has_input(char **args);
// int		apply_input_redir(char **args);
// void	restore_stdin(int save_stdin);
// int		arr_len(char **arr);
// int		has_pipe(char **args);
// void	execute_pipe(char **args, t_env *env);
// void	execute_pipeline(char **args);
// char	**copy_args(char **args, int start, int end);
// int		init_pipe(t_pipe *p, char **args);
// char	**get_cmd_part(char **args, int start, int end);
// int		get_pipe_paths(char **cmd1, char **cmd2, char **path1, char **path2);
// void	exec_pipe_left(int *fd, char *path, char **cmd, t_env *env);
// void	exec_pipe_right(int *fd, char *path, char **cmd, t_env *env);

#endif
