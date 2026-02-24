/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 16:51:00 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/24 18:03:01 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_1cmd(t_cmd *cmd, t_env *env)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	setup_redirections(cmd);
	g_exit_status = exec_builtin(cmd, &env);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return ;
}

void	execute(t_cmd *cmd, t_env *env)
{
	int		p[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	if (!cmd->next && is_builtin(cmd))
	{
		exec_1cmd(cmd, env);
		return ;
	}
	while (cmd)
	{
		if (cmd->next)
			pipe(p);
		pid = fork();
		if (pid == 0)
			exec_child(cmd, env, prev_fd, p);
		if (prev_fd != -1)
			close(prev_fd);
		prev_fd = -1;
		if (cmd->next && !close(p[1]))
			prev_fd = p[0];
		cmd = cmd->next;
	}
	wait_all(pid);
}

/*void	execute(t_cmd *cmd, t_env *env)
{
	int		p[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	if (cmd && !cmd->next && is_builtin(cmd))
	{
		g_exit_status = exec_builtin(cmd, &env);
		return ;
	}
	while (cmd)
	{
		if (cmd->next)
			pipe(p);
		pid = fork();
		if (pid == 0)
			exec_child(cmd, env, prev_fd, p);
		if (prev_fd != -1)
			close(prev_fd);
		prev_fd = -1;
		if (cmd->next && !close(p[1]))
			prev_fd = p[0];
		cmd = cmd->next;
	}
	wait_all(pid);
}*/

void	exec_child(t_cmd *cmd, t_env *env, int prev_fd, int pipe_fd[2])
{
	set_child_signals();
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	setup_redirections(cmd);
	if (is_builtin(cmd))
		exit(exec_builtin(cmd, &env));
	exec_external(cmd, env);
	exit(127);
}

void	exec_parent(t_cmd *cmd, int *prev_fd, int pipe_fd[2])
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	else
	{
		if (*prev_fd != -1)
			close(*prev_fd);
		*prev_fd = -1;
	}
}

void	exec_external(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**envp;
	int		fd;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		exit(0);
	path = get_cmd_path(cmd->argv[0], env);
	if (!path)
	{
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	envp = convert_env_to_array(env);
	fd = 2;
	while (++fd < 1024)
		close(fd);
	execve(path, cmd->argv, envp);
	perror("execve");
	free(path);
	free_split(envp);
	exit(126);
}

/*void    wait_all(pid_t last_pid) in expansion
{
	int     status;
	pid_t   pid;

	while ((pid = wait(&status)) > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				// Si l'enfant a été stoppé par CTRL-\ (SIGQUIT)
				if (WTERMSIG(status) == SIGQUIT)
					ft_putstr_fd("Quitter (core dumped)\n", 1);
				else if (WTERMSIG(status) == SIGINT)
					ft_putstr_fd("\n", 1);
				g_exit_status = 128 + WTERMSIG(status);
			}
		}
	}
}
*/