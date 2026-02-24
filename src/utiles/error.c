/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 18:27:58 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/24 12:10:15 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
	return (1);
}

int	perror_msg(char *prefix, char *arg)
{
	ft_putstr_fd(prefix, 2);
	ft_putstr_fd(": ", 2);
	perror(arg);
	return (1);
}

int	syntax_error(char *msg)
{
	ft_putstr_fd("minishell: syntax error", 2);
	if (msg)
	{
		ft_putstr_fd(" near ", 2);
		ft_putstr_fd(msg, 2);
	}
	ft_putchar_fd('\n', 2);
	g_exit_status = 1;
	return (0);
}
