/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 18:29:50 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/24 22:57:31 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_token_type type)
{
	return (type == REDIR_IN
		|| type == REDIR_OUT
		|| type == REDIR_APPEND
		|| type == HEREDOC);
}

int	open_redir_file(t_redir *r)
{
	int	fd;

	if (!r->file || r->file[0] == '\0')
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		return (-1);
	}
	if (r->type == REDIR_IN)
		fd = open(r->file, O_RDONLY);
	else if (r->type == REDIR_OUT)
		fd = open(r->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (r->type == REDIR_APPEND)
		fd = open(r->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		return (-1);
	if (fd < 0)
		perror(r->file);
	return (fd);
}

static int	apply_single_redir(t_redir *r)
{
	int	fd;

	if (r->type == HEREDOC)
	{
		if (dup2(r->heredoc_fd, STDIN_FILENO) < 0)
			return (perror("dup2"), -1);
		close(r->heredoc_fd);
		return (0);
	}
	fd = open_redir_file(r);
	if (fd < 0)
		return (-1);
	if (r->type == REDIR_IN)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
			return (close(fd), perror("dup2"), -1);
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
			return (close(fd), perror("dup2"), -1);
	}
	close(fd);
	return (0);
}

int	setup_redirections(t_cmd *cmd)
{
	t_redir	*r;

	r = cmd->redir;
	while (r)
	{
		if (apply_single_redir(r) < 0)
			return (-1);
		r = r->next;
	}
	return (0);
}
