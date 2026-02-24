/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:15:18 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/24 11:29:32 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_find(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	set_env_value(char *key, char *value, t_env **env)
{
	t_env	*node;

	if (!key || !env)
		return (1);
	node = env_find(*env, key);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(value);
	}
	else
	{
		node = env_new(ft_strdup(key), ft_strdup(value));
		env_add_back(env, node);
	}
	return (0);
}

int	unset_env_value(char *key, t_env **env)
{
	t_env	*curr;
	t_env	*prev;

	if (!key || !env || !*env)
		return (1);
	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (1);
}

int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**convert_env_to_array(t_env *env)
{
	char	**array;
	char	*tmp;
	int		i;
	int		size;

	size = env_size(env);
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		array[i] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
/*

// 设置环境变量
int	set_env_value(char *key, char *value, t_env **env)
{
	t_env	*curr;

	if (!key || !value || !env)
		return (0);
	curr = *env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			free(curr->value);
			curr->value = ft_strdup(value);
			return (1);
		}
		curr = curr->next;
	}
	// 未找到，添加新节点
	curr = env_new(key, value);
	curr->next = *env;
	*env = curr;
	return (1);
}

// 删除环境变量
int	unset_env_value(char *key, t_env **env)
{
	t_env	*curr;
	t_env	*prev;

	if (!key || !env || !*env)
		return (0);
	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return (1);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
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

*/