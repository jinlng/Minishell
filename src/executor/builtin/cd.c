/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:33:03 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/24 15:49:05 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_error(char *msg, char *arg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
	g_exit_status = 1;
	return (1);
}

void	update_pwd(t_env *env, char *oldpwd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		set_env_value("OLDPWD", oldpwd, &env);
		set_env_value("PWD", cwd, &env);
		free(cwd);
	}
}

int	builtin_cd(char **args, t_env **env)
{
	char	*path;
	char	oldpwd[1024];
	char	*oldpwd_ptr;

	if (!getcwd(oldpwd, sizeof(oldpwd)))
		oldpwd_ptr = get_env_value("PWD", *env);
	else
		oldpwd_ptr = ft_strdup(oldpwd);
	if (args[1] && args[2])
		return (free(oldpwd_ptr), cd_error("too many arguments", NULL));
	path = get_cd_path(args, *env);
	if (!path)
		return (free(oldpwd_ptr), 1);
	if (chdir(path) == -1)
		return (g_exit_status = 1, free(oldpwd_ptr),
			cd_error("No such file or directory", args[1]));
	update_pwd(*env, oldpwd_ptr);
	free(oldpwd_ptr);
	g_exit_status = 0;
	return (0);
}

/*int	builtin_cd(char **args, t_env **env)
{
	char	*path;
	char	oldpwd[1024];
	char	*oldpwd_ptr;

	if (!getcwd(oldpwd, sizeof(oldpwd)))
		oldpwd_ptr = get_env_value("PWD", *env);
	else
		oldpwd_ptr = ft_strdup(oldpwd);
	if (args[1] && args[2])
	{
		free(oldpwd_ptr);
		return (cd_error("too many arguments", NULL));
	}
	path = get_cd_path(args, *env);
	if (!path)
	{
		free(oldpwd_ptr);
		return (1);
	}
	if (chdir(path) == -1)
	{
		free(oldpwd_ptr);
		return (cd_error("No such file or directory", args[1]));
	}
	update_pwd(*env, oldpwd_ptr);
	free(oldpwd_ptr);
	g_exit_status = 0;
	return (0);
}*/

/*int builtin_cd(char **args, t_env **env)
{
	char    *path;
	char    *oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (cd_error("getcwd error", NULL));
	if (args[1] && args[2])
		return (cd_error("too many arguments", NULL));

	if (!getcwd(oldpwd, sizeof(oldpwd)))
		return (cd_error("getcwd error", NULL));

	path = get_cd_path(args, *env);
	if (!path)
		return (1);

	if (chdir(path) == -1)
		return (cd_error("No such file or directory", args[1]));

	update_pwd(*env, oldpwd);
	free(oldpwd);
	// return (0);
	return (g_exit_status);
}*/
