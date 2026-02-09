/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:58:57 by potabaga          #+#    #+#             */
/*   Updated: 2026/02/08 18:06:18 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    execute_cmd(char **args, t_env *env)
{
	pid_t   pid;
	char    *cmd;
	int     redir;
	int     fd;
	int     status;
	
	cmd = get_cmd_path(args[0]);
	if (!cmd)
	{
		printf("%s: command not found\n", args[0]);
		env->last_status = 127; 
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		set_child_signals();
		redir = has_redir(args);
		if (redir != -1)
		{
			fd = open(args[redir + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				exit(1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			args[redir] = NULL;
		}
		execve(cmd, args, env->env);
		perror("execve");
		exit(127);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		env->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		env->last_status = 128 + WTERMSIG(status);
	free(cmd);
}

void    builtin_echo_with_redir(char **args, t_env *env) 
{
	int redir;
	int fd;
	int save_stdout;

	redir = has_redir(args);
	if (redir == -1)
	{
		builtin_echo(args, env);
		return ;
	}
	if (!args[redir + 1])
	{
		printf("minishell: syntax error\n");
		env->last_status = 2; 
		return ;
	}
	fd = open(args[redir + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		env->last_status = 1; 
		return ;
	}    
	save_stdout = dup(STDOUT_FILENO);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return ;
	}
	close(fd);
	char *temp = args[redir];
	args[redir] = NULL;
	
	builtin_echo(args, env);
	args[redir] = temp;
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdout);
}
void	restore_stdout(int save_stdout)
{
	if (save_stdout >= 0)
	{
		dup2(save_stdout, STDOUT_FILENO);
		close(save_stdout);
	}
}

void    process_line(char *line, t_env *env)
{
	char	**args;
	int		save_stdout;
	int		save_stdin;

	add_history(line);
	args = parse_line(line);
	if (!args || !args[0])
		return (free_args(args));
	if (has_pipe(args) != -1)
	{
		execute_pipe(args, env);
		free_args(args);
		return ;
	}
	save_stdout = apply_redir(args);
	save_stdin = apply_input_redir(args);
	if (save_stdout == -2 || save_stdin == -2)
	{
		env->last_status = 1;
		free_args(args);
		return ;
	}
	if (ft_strcmp(args[0], "pwd") == 0)
		builtin_pwd(env);
	else if (ft_strcmp(args[0], "echo") == 0)
		builtin_echo(args, env);
	else if (ft_strcmp(args[0], "cd") == 0)
		builtin_cd(args, env);
	else if (ft_strcmp(args[0], "env") == 0)
		builtin_env(env);
	else if (ft_strcmp(args[0], "export") == 0)
		builtin_export(args, env);
	else if (ft_strcmp(args[0], "exit") == 0)
		builtin_exit(args, env);
	else
		execute_cmd(args, env);
	restore_stdout(save_stdout);
	restore_stdin(save_stdin);
	free_args(args);
}
