/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 18:29:50 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/13 18:32:27 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redir_file(t_redir *r)
{
	int	fd;

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

void	setup_redirections(t_cmd *cmd)
{
	t_redir *r;
	int	fd;

	r = cmd->redir;
	while (r)
	{
		if (r->type == REDIR_IN)
		{
			fd = open(r->file, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (r->type == REDIR_OUT)
		{
			fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (r->type == REDIR_APPEND)
		{
			fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (r->type == HEREDOC)
    	{
			dup2(r->heredoc_fd, STDIN_FILENO);
			close(r->heredoc_fd);
		}
		r = r->next;
	}
}