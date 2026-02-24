/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:57:37 by potabaga          #+#    #+#             */
/*   Updated: 2026/02/24 22:39:40 by potabaga         ###   ########.fr       */
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
# include <limits.h>

/* ONLY ONE global variable */
extern int	g_exit_status;

typedef struct s_env
{
	char			**env;
	int				last_status;
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
typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}	t_token_type;

/* types of quote */
typedef enum e_quote
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}	t_quote;

/* Token structure */
typedef struct s_token
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
typedef struct s_cmd
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
void	*create_operator_token(t_token **tokens, char *input, int *i);
t_token	*lexer(char *input);
char	*extract_word(char *s, int *i, t_quote *quote);
// char	*build_word_without_quotes(char *src, int len, t_quote quote);

/* expansion tools & expansion */
int		is_var_char(char c);
char	*get_env_value(char *name, t_env *env);
int		get_var_name_len(char *str);
// char	*expand_str(char *str, t_env *env);
char	*char_join_free(char *s1, char c);
char	*str_join_free(char *s1, char *s2);
char	*expand_string(char *str, t_env *env);
char	*expand_variable(char *str, int *i, t_env *env);
void	expand_tokens(t_token *tok, t_env *env);

/* parser tools & parser */
t_cmd	*init_cmd(void);
void	add_arg(t_cmd *cmd, char *arg);
void	add_redir(t_cmd *cmd, t_token_type type, char *file, t_quote quote);
int		handle_pipe(t_cmd **cur);
int		handle_redir(t_cmd *cur, t_token **tok);
t_cmd	*parser(t_token *tok);
int		check_syntax(t_token *tok);
t_token	*get_last_token(t_token *tok);

/* heredoc*/
int		process_heredocs(t_cmd *cmd);
int		prepare_heredoc(t_redir *r);
void	heredoc_child(int fd[2], t_redir *r);

/* builtin functions */
int		builtin_echo(char **argv, t_env **env);

int		cd_error(char *msg, char *arg);
void	update_pwd(t_env *env, char *oldpwd);
int		builtin_cd(char **argv, t_env **env);

int		builtin_pwd(char **argv, t_env **env);
int		builtin_unset(char **argv, t_env **env);
void	unset_variable(char *key, t_env **env);
int		builtin_env(char **argv, t_env **env);
int		builtin_exit(char **argv, t_env **env);

int		is_valid_identifier(char *s);
void	handle_export_arg(char *arg, t_env **env, int *status);
void	print_export(t_env *env);
int		builtin_export(char **argv, t_env **env);

/* builtin dispatcher */
int		is_builtin(t_cmd *cmd);
int		exec_builtin(t_cmd *cmd, t_env **env);

/* signal */
void	set_parent_signals(void);
void	set_child_signals(void);
void	heredoc_sigint(int sig);
void	set_heredoc_signals(void);
void	set_exit_status(int status);

/* exacution */
void	execute(t_cmd *cmd, t_env *env);

void	exec_1cmd(t_cmd *cmd, t_env *env);
void	exec_child(t_cmd *cmd, t_env *env, int prev_fd, int pipe_fd[2]);
void	exec_parent(t_cmd *cmd, int *prev_fd, int pipe_fd[2]);
void	exec_external(t_cmd *cmd, t_env *env);
void	wait_all(pid_t last_pid);

/* pipe */
int		create_pipe_if_needed(t_cmd *cmd, int pipe_fd[2]);

/* REDIRECTIONS */
int		is_redir(t_token_type type);
int		open_redir_file(t_redir *r);
int		setup_redirections(t_cmd *cmd);

/* helper functions */
int		is_numeric(char *s);

/* Debug Printer */
void	print_tokens(t_token *tok);
void	print_cmds(t_cmd *cmd);

/* init env */
t_env	*init_env(char **envp);
t_env	*env_new(char *key, char *value);
t_env	*create_env_node(char *str);
void	env_add_back(t_env **env, t_env *new);

t_env	*env_find(t_env *env, char *key);
int		set_env_value(char *key, char *value, t_env **env);
int		unset_env_value(char *key, t_env **env);
int		env_size(t_env *env);
char	**convert_env_to_array(t_env *env);

/* path */
char	*get_cmd_path(char *cmd, t_env *env);
char	**convert_env_to_array(t_env *env);
char	*get_cd_path(char **args, t_env *env);

/* free related */
void	free_tokens(t_token *tok);
void	free_redir(t_redir *redir);
void	free_cmd(t_cmd *cmd);
void	free_env(t_env **env);
// void	free_env(t_env *env);
void	free_split(char **arr);
void	free_envp(char **envp);
void	free_all_global(t_env *env);

/* error */
int		error_msg(char *msg);
int		perror_msg(char *prefix, char *arg);
int		syntax_error(char *msg);

/* prompt hub */
void	sigint_prompt(int sig);
char	*create_prompt(t_env *env);
char	*read_line_with_prompt(t_env *env);

/* main */
void	process_command_line(char *line, t_env *env);
void	minishell_loop(t_env *env);

#endif