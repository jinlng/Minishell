/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:33:03 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/13 17:37:09 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char **argv, t_env **env)
{
	char	*path;

	if (!argv[1])
		path = get_env_value("HOME", *env);
	else
		path = argv[1];

	if (!path || chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
