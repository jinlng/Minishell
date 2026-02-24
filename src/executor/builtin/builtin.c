/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 16:54:45 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/24 11:52:24 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin	g_builtins[] = {
{"echo", builtin_echo},
{"cd", builtin_cd},
{"pwd", builtin_pwd},
{"export",	builtin_export},
{"unset",	builtin_unset},
{"env",	builtin_env},
{"exit",	builtin_exit},
{NULL, NULL}
};

int	is_builtin(t_cmd *cmd)
{
	int	i;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	i = 0;
	while (g_builtins[i].name)
	{
		if (ft_strcmp(cmd->argv[0], g_builtins[i].name) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	exec_builtin(t_cmd *cmd, t_env **env)
{
	int	i;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	i = 0;
	while (g_builtins[i].name)
	{
		if (ft_strcmp(cmd->argv[0], g_builtins[i].name) == 0)
			return (g_builtins[i].func(cmd->argv, env));
		i++;
	}
	return (1);
}
