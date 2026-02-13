/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 16:51:00 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/13 18:50:56 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_cmd *cmd, t_env *env)
{
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	if (!cmd->next && is_builtin(cmd))
	{
		exec_builtin(cmd, &env);
		return ;
	}
	while (cmd)
	{
		if (cmd->next)
			pipe(pipe_fd);

		pid = fork();
		if (pid == 0)
			exec_child(cmd, env, prev_fd, pipe_fd);
		else
			exec_parent(cmd, &prev_fd, pipe_fd, pid);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		cmd = cmd->next;
	}

	wait_all();
}

void	exec_child(t_cmd *cmd, t_env *env, int prev_fd, int pipe_fd[2])
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}

	if (cmd->pipe_out)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}

	setup_redirections(cmd);

	if (is_builtin(cmd))
		exec_builtin(cmd, &env);
	else
		exec_external(cmd, env);
}

void	exec_parent(t_cmd *cmd, int *prev_fd, int pipe_fd[2], pid_t pid)
{
	(void)pid;
	if (*prev_fd != -1)
		close(*prev_fd);

	if (cmd->pipe_out)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	else
		*prev_fd = -1;
}

void	exec_external(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**envp;

	path = get_cmd_path(cmd->argv[0], env);
	if (!path)
	{
		printf("%s: command not found\n", cmd->argv[0]);
		exit(127);
	}
	envp = convert_env_to_array(env);
	execve(path, cmd->argv, envp);
	perror("execve");
	exit(126);
}

void	wait_all(void)
{
	int	status;

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
	}
}
