/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 18:32:56 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/13 18:33:33 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

char	*get_cmd_path(char *cmd, t_env *env)
{
	char	*path;
	char	**dirs;
	char	*full;
	int		i;

	if (!cmd)
		return (NULL);

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}

	path = get_env_value("PATH", env);
	if (!path)
		return (NULL);

	dirs = ft_split(path, ':');
	i = 0;
	while (dirs[i])
	{
		full = join_path(dirs[i], cmd);
		if (access(full, X_OK) == 0)
		{
			free_split(dirs);
			return (full);
		}
		free(full);
		i++;
	}
	free_split(dirs);
	return (NULL);
}
