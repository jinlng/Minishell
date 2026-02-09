/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:10:15 by potabaga          #+#    #+#             */
/*   Updated: 2026/01/23 12:25:48 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int has_redir(char **args)
{
	int i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	has_append(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], ">>") == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	apply_redir(char **args)
{
	int	i;
	int	fd;
	int	save_stdout;

	if (!args)
		return (-1);

	i = has_append(args);
	if (i != -1)
	{
		if (!args[i + 1])
			return (printf("minishell: syntax error\n"), -2);
		fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		i = has_redir(args);
		if (i == -1)
			return (-1);
		if (!args[i + 1])
			return (printf("minishell: syntax error\n"), -2);
		fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (fd < 0)
		return (perror("open"), -2);

	save_stdout = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	args[i] = NULL;
	return (save_stdout);
}

/*int	apply_redir(char **args)
{
	int	redir;
	int	fd;
	int	save_stdout;

	redir = has_redir(args);
	if (redir == -1)
		return (-1);
	if (!args[redir + 1])
	{
		printf("minishell: syntax error\n");
		return (-2);
	}
	fd = open(args[redir + 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		return (-2);
	}
	save_stdout = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	args[redir] = NULL;
	return (save_stdout);
}*/