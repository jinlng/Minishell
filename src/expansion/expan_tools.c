/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 19:54:57 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/11 22:03:35 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/* Retrieves the value of an environment variable from t_env */
char	*get_env_value(char *name, t_env *env)
{
	int		idx;
	char	*val;

	if (ft_strncmp(name, "?", 2) == 0)
		return (ft_itoa(env->last_status));
	if (ft_strncmp(name, "0", 2) == 0)
		return (ft_strdup("minishell"));
	idx = env_index(env, name);
	if (idx == -1)
		return (ft_strdup(""));
	val = ft_strchr(env->env[idx], '=');
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val + 1));
}

/* Finds the end of a variable name starting after '$' */
int	get_var_name_len(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?' || str[i] == '0')
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}
