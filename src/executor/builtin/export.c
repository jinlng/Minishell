/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:33:36 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/13 18:59:53 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(char **argv, t_env **env)
{
	int	i;

	g_exit_status = 0;
	if (!argv[1])
	{
		/* 如果没有参数，打印当前环境 */
		t_env *cur = *env;
		while (cur)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(cur->key, 1);
			if (cur->value)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(cur->value, 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
			cur = cur->next;
		}
		return (0);
	}

	i = 1;
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_exit_status = 1;
		}
		else
			env_set(env, argv[i]);
		i++;
	}
	return (g_exit_status);
}

