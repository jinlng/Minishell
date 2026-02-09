/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:40:02 by potabaga          #+#    #+#             */
/*   Updated: 2026/02/08 18:00:44 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int has_pipe(char **args)
{
	int i = 0;

	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	arr_len(char **arr)
{
	int i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**copy_args(char **args, int start, int end)
{
	char	**out;
	int		i = 0;

	out = malloc(sizeof(char *) * (end - start + 1));
	while (start < end)
	{
		out[i++] = ft_strdup(args[start]);
		start++;
	}
	out[i] = NULL;
	return (out);
}

int	init_pipe(t_pipe *p, char **args)
{
	int	i;

	i = has_pipe(args);
	if (i == -1)
		return (0);
	p->cmd1 = get_cmd_part(args, 0, i);
	p->cmd2 = get_cmd_part(args, i + 1, arr_len(args));
	if (!get_pipe_paths(p->cmd1, p->cmd2, &p->path1, &p->path2))
		return (0);
	if (pipe(p->fd) == -1)
		return (0);
	return (1);
}

void	execute_pipe(char **args,t_env *env)
{
	t_pipe	p;
	int		status;

	if (!init_pipe(&p, args))
		return ;
	p.pid1 = fork();
	if (p.pid1 == 0)
		exec_pipe_left(p.fd, p.path1, p.cmd1, env);
	p.pid2 = fork();
	if (p.pid2 == 0)
		exec_pipe_right(p.fd, p.path2, p.cmd2, env);
	close(p.fd[0]);
	close(p.fd[1]);
	waitpid(p.pid1, NULL, 0);
	waitpid(p.pid2, &status, 0);
	if (WIFEXITED(status))
		env->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
        env->last_status = 128 + WTERMSIG(status);
	free(p.path1);
	free(p.path2);
	free_args(p.cmd1);
	free_args(p.cmd2);
}

