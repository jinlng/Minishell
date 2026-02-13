/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:15:18 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/13 19:00:49 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_env *env, char **envp)
{
	int	i;
	int	count;

	count = 0;
	while (envp[count])
		count++;
	env->env = malloc(sizeof(char *) * (count + 1));
	if (!env->env)
		return ;
	i = 0;
	while (i < count)
	{
		env->env[i] = ft_strdup(envp[i]);
		i++;
	}
	env->env[i] = NULL;
	env->last_status = 0;
}

int	env_index(t_env *env, char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (env->env[i])
	{
		if (ft_strncmp(env->env[i], name, len) == 0 && env->env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	env_set(t_env **env, char *arg)
{
	char	*key;
	char	*value;
	t_env	*cur;

	cur = *env;
	key = NULL;
	value = NULL;

	/* 分割 key=value */
	if (ft_strchr(arg, '='))
	{
		key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
		value = ft_strdup(ft_strchr(arg, '=') + 1);
	}
	else
		key = ft_strdup(arg);

	/* 检查是否存在 */
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			free(cur->value);
			cur->value = value ? value : ft_strdup("");
			free(key);
			return ;
		}
		cur = cur->next;
	}

	/* 不存在，创建新节点 */
	cur = malloc(sizeof(t_env));
	cur->key = key;
	cur->value = value ? value : ft_strdup("");
	cur->next = *env;
	*env = cur;
}

int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->value)
			i++;
		env = env->next;
	}
	return (i);
}

char	**convert_env_to_array(t_env *env)
{
	char	**envp;
	char	*tmp;
	int		i;

	envp = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!envp)
		return (NULL);

	i = 0;
	while (env)
	{
		if (env->value)
		{
			tmp = ft_strjoin(env->key, "=");
			envp[i] = ft_strjoin(tmp, env->value);
			free(tmp);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

