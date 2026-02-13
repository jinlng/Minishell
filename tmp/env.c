/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 18:44:32 by potabaga          #+#    #+#             */
/*   Updated: 2026/02/08 17:28:31 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	g_env;

void    init_env(t_env *env, char **envp)
{
    int i;

    env->last_status = 0;
    i = 0;
    while (envp[i])
        i++;
    env->env = malloc(sizeof(char *) * (i + 1));
    if (!env->env)
        return ; 
    i = 0;
    while (envp[i])
    {
        env->env[i] = ft_strdup(envp[i]);
        i++;
    }
    env->env[i] = NULL;
}

int	env_index(t_env *env, char *name)
{
	int		i;
	size_t	len;

	len = 0;
	if (!env || !env->env)
        return (-1);
	while (name[len] && name[len] != '=')
		len++;
	i = 0;
	while (env->env[i])
	{
		if (ft_strncmp(env->env[i], name, len) == 0
			&& env->env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void    env_set(t_env *env, char *args) 
{
    int     i;
    int     idx;
    char    **new_env;

    if (!env || !args)
        return ;
    idx = env_index(env, args); 
    if (idx >= 0)
    {
        free(env->env[idx]);
        env->env[idx] = ft_strdup(args);
        return ;
    }
    i = 0;
    while (env->env[i])
        i++;
    new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env)
        return ;
    i = 0;
    while (env->env[i])
    {
        new_env[i] = env->env[i];
        i++;
    }
    new_env[i] = ft_strdup(args); 
    new_env[i + 1] = NULL;       
    free(env->env);
    env->env = new_env;          
}

