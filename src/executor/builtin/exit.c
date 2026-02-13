/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:34:01 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/13 19:06:42 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(char **argv, t_env **env)
{
	long	status;

	(void)env;
	printf("exit\n");

	if (!argv[1])
		exit(0);

	if (!is_numeric(argv[1]))
	{
		printf("exit: numeric argument required\n");
		exit(255);
	}
	if (argv[2])
	{
		printf("exit: too many arguments\n");
		return (1);
	}
	status = ft_atol(argv[1]);
	exit((unsigned char)status);
}
