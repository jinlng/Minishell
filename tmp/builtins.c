/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:59:36 by potabaga          #+#    #+#             */
/*   Updated: 2026/02/08 17:20:10 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(t_env *env)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		env->last_status = 0;
	}
	else
	{
		perror("pwd");
		env->last_status = 0;
	}
}

void	builtin_echo(char **args, t_env *env)
{
	int	i;
	int	newline;

	(void)env;
	i = 1;
	newline = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}

void	builtin_cd(char **args, t_env *env)
{
	if (!args[1])
	{
		printf("cd: missing argument\n");
		return ;
	}
	if (chdir(args[1]) != 0)
		{
			perror("cd");
			env->last_status = 1;
			return ;
		}
	env->last_status = 0;
}

void	builtin_env(t_env *env)
{
	int	i;

	i = 0;
	if (!env || !env->env)
        return ;
	while (env->env[i])
	{
		printf("%s\n", env->env[i]);
		i++;
	}
}

void	builtin_export(char **args, t_env *env)
{
	int	i;

	if (!args[1])
	{
		builtin_env(env);
		return ;
	}
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			printf("minishell: export: `%s': not a valid identifier\n", args[i]);
			env->last_status = 1;
		}
		else if (ft_strchr(args[i], '='))
		{
			env_set(env, args[i]);
			env->last_status = 0;
		}
		i++;
	}
}


/*void	builtin_exit(char **args)
{
	int	status;

	status = 0;
	if (args[1])
		status = ft_atoi(args[1]);
	printf("exit\n");
	exit(status);
}*/
