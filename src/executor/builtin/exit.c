/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:34:01 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/24 21:13:29 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(char **args, t_env **env)
{
	int	exit_code;

	ft_putendl_fd("exit", 1);
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit_code = 2;
		}
		else if (args[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			return (1);
		}
		else
			exit_code = ft_atoi(args[1]) % 256;
	}
	else
		exit_code = g_exit_status;
	free_env(env);
	clear_history();
	exit(exit_code);
}

/*int	builtin_exit(char **argv, t_env **env)
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
}*/
