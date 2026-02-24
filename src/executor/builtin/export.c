/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:33:36 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/24 22:42:25 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/*void	handle_export_arg(char *arg, t_env **env, int *status)
{
	char	*equal;
	char	*key;
	char	*value;

	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		*status = 1;
		return ;
	}
	equal = ft_strchr(arg, '=');
	if (equal)
	{
		key = ft_substr(arg, 0, equal - arg);
		value = ft_strdup(equal + 1);
		if (value[0] == '\0')
		{
			if (env_find(*env, key))
				set_env_value(key, value, env);
		}
		else
			set_env_value(key, value, env);
		free(key);
		free(value);
	}
	else
	{
		if (!env_find(*env, arg))
			set_env_value(arg, "", env);
	}
}*/
void	handle_export_arg(char *arg, t_env **env, int *status)
{
	char	*equal;
	char	*key;
	char	*value;

	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2),
		ft_putstr_fd("': not a valid identifier\n", 2);
		return ((void)(*status = 1));
	}
	equal = ft_strchr(arg, '=');
	if (equal)
	{
		key = ft_substr(arg, 0, equal - arg);
		value = ft_strdup(equal + 1);
		if (value[0] != '\0' || env_find(*env, key))
			set_env_value(key, value, env);
		free(key);
		free(value);
	}
	else if (!env_find(*env, arg))
		set_env_value(arg, "", env);
}

void	print_export(t_env *env)
{
	while (env)
	{
		printf("export %s", env->key);
		if (env->value)
			printf("=\"%s\"", env->value);
		printf("\n");
		env = env->next;
	}
}

int	builtin_export(char **argv, t_env **env)
{
	int	i;
	int	status;

	if (!argv[1])
	{
		print_export(*env);
		return (0);
	}
	i = 1;
	status = 0;
	while (argv[i])
	{
		handle_export_arg(argv[i], env, &status);
		i++;
	}
	g_exit_status = status;
	return (status);
}

// int	builtin_export(char **argv, t_env **env)
// {
// 	int	i;

// 	g_exit_status = 0;
// 	if (!argv[1])
// 	{
// 		/* 如果没有参数，打印当前环境 */
// 		t_env *cur = *env;
// 		while (cur)
// 		{
// 			ft_putstr_fd("declare -x ", 1);
// 			ft_putstr_fd(cur->key, 1);
// 			if (cur->value)
// 			{
// 				ft_putstr_fd("=\"", 1);
// 				ft_putstr_fd(cur->value, 1);
// 				ft_putstr_fd("\"", 1);
// 			}
// 			ft_putstr_fd("\n", 1);
// 			cur = cur->next;
// 		}
// 		return (0);
// 	}

// 	i = 1;
// 	while (argv[i])
// 	{
// 		if (!is_valid_identifier(argv[i]))
// 		{
// 			ft_putstr_fd("minishell: export: `", 2);
// 			ft_putstr_fd(argv[i], 2);
// 			ft_putstr_fd("': not a valid identifier\n", 2);
// 			g_exit_status = 1;
// 		}
// 		else
// 			set_env_value(env->key, env.arg, argv[i]);
// 		i++;
// 	}
// 	return (g_exit_status);
// }