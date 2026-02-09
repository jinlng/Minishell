/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:44:19 by potabaga          #+#    #+#             */
/*   Updated: 2026/02/08 17:55:53 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_cmd_part(char **args, int start, int end)
{
	return (copy_args(args, start, end));
}

int	get_pipe_paths(char **cmd1, char **cmd2, char **path1, char **path2)
{
	*path1 = get_cmd_path(cmd1[0]);
	*path2 = get_cmd_path(cmd2[0]);
	if (!*path1 || !*path2)
	{
		printf("minishell: command not found\n");
		return (0);
	}
	return (1);
}

void	exec_pipe_left(int *fd, char *path, char **cmd, t_env *env)
{
	set_child_signals();
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (path)
        execve(path, cmd, env->env);
    perror("minishell: execve");
	exit(1);
}

void    exec_pipe_right(int *fd, char *path, char **cmd, t_env *env) 
{
<<<<<<< HEAD
	set_child_signals();
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	apply_redir(cmd); 
	execve(path, cmd, g_env.env);
	exit(1);
=======
    set_child_signals();
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    close(fd[1]);

    apply_redir(cmd); 
    if (path)
        execve(path, cmd, env->env);
    perror("minishell: execve");
    exit(1);
>>>>>>> 1105e17 (new)
}

