/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 18:29:08 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/13 18:29:21 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipe_if_needed(t_cmd *cmd, int pipe_fd[2])
{
	if (cmd->next)
	{
		if (pipe(pipe_fd) == -1)
			return (perror("pipe"), 1);
	}
	return (0);
}
