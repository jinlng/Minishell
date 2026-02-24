/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 19:54:57 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/24 12:08:39 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/* Retrieves the value of an environment variable from t_env */
// char	*get_env_value(char *name, t_env *env)
// {
// 	int		idx;
// 	char	*val;

// 	if (ft_strncmp(name, "?", 2) == 0)
// 		return (ft_itoa(g_exit_status));
// 	if (ft_strncmp(name, "0", 2) == 0)
// 		return (ft_strdup("minishell"));
// 	idx = env_index(env, name);
// 	if (idx == -1)
// 		return (ft_strdup(""));
// 	val = ft_strchr(env->env[idx], '=');
// 	if (!val)
// 		return (ft_strdup(""));
// 	return (ft_strdup(val + 1));
// }

char	*get_env_value(char *name, t_env *env)
{
	t_env	*tmp;

	if (!name || !env)
		return (NULL);
	if (ft_strcmp(name, "?") == 0)
		return (ft_itoa(g_exit_status));
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, name) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
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

char	*char_join_free(char *s1, char c)
{
	char	*new;
	int		len;

	len = ft_strlen(s1);
	new = malloc(len + 2);
	if (!new)
		return (NULL);
	ft_memcpy(new, s1, len);
	new[len] = c;
	new[len + 1] = '\0';
	free(s1);
	return (new);
}

char	*str_join_free(char *s1, char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (new);
}
