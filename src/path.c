/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 18:32:56 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/23 21:12:55 by potabaga         ###   ########.fr       */
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
	char	**dirs;
	char	*full;
	char	*path;
	int		i;

	if (cmd && ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path = get_env_value("PATH", env);
	if (!path || !*path)
		return (free(path), NULL);
	dirs = ft_split(path, ':');
	free(path);
	i = -1;
	while (dirs && dirs[++i])
	{
		full = join_path(dirs[i], cmd);
		if (full && access(full, X_OK) == 0)
			return (free_split(dirs), full);
		free(full);
	}
	return (free_split(dirs), NULL);
}

/*char	*get_cmd_path(char *cmd, t_env *env)
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
}*/

/*
** 获取目标路径
*/
char	*get_cd_path(char **args, t_env *env)
{
	char	*path;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		return (get_env_value("HOME", env));
	if (ft_strcmp(args[1], "-") == 0)
	{	
		path = get_env_value("OLDPWD", env);
		if (!path)
		{
			cd_error("OLDPWD not set", NULL);
			return (NULL);
		}
		ft_putendl_fd(path, 1);
		return (path);
	}
	return (args[1]);
}
