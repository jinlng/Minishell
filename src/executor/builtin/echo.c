/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:22:09 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/13 18:48:41 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **argv, t_env **env)
{
	int	i;
	int	n_flag;

	(void)env;
	i = 1;
	n_flag = 0;

	if (argv[i] && ft_strcmp(argv[i], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}

	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putchar_fd('1', 1);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);

	g_exit_status = 0;
	return (0);
}
