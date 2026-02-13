/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 18:27:58 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/13 18:28:15 by jinliang         ###   ########.fr       */
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
