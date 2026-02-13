/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 19:18:58 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/13 19:57:34 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_var(char *res, char *str, int *i, t_env *env)
{
	int		len;
	char	*name;
	char	*val;
	char	*tmp;

	len = get_var_name_len(&str[*i + 1]);
	name = ft_substr(str, *i + 1, len);
	val = get_env_value(name, env);
	tmp = res;
	res = ft_strjoin(res, val);
	free(tmp);
	free(name);
	free(val);
	*i += len + 1;
	return (res);
}

static char	*append_char(char *res, char c)
{
	char	*tmp;
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	tmp = res;
	res = ft_strjoin(res, str);
	free(tmp);
	return (res);
}

static char	*append_dollar(char *res, int *i)
{
	char	*tmp;

	tmp = res;
	res = ft_strjoin(res, "$");
	free(tmp);
	(*i)++;
	return (res);
}

/* Expands all variables in a single string */
char	*expand_str(char *str, t_env *env)
{
	int		i;
	char	*res;

	if (!str)
		return (NULL);
	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1]
			&& (is_var_char(str[i + 1]) || str[i + 1] == '?'))
			res = append_var(res, str, &i, env);
		else if (str[i] == '$' && (!str[i + 1] || is_whitespace(str[i + 1])))
			res = append_dollar(res, &i);
		else
		{
			res = append_char(res, str[i]);
			i++;
		}
	}
	// free(str);
	return (res);
}

/* Iterates through tokens and expands variables in WORD types */
void	expand_tokens(t_token *token, t_env *env)
{
	t_token	*tok;
	char	*expanded;

	tok = token;
	while (tok)
	{
		if (tok->type == WORD && tok->quote != Q_SINGLE)
		{
			expanded = expand_str(tok->value, env);
			free(tok->value);
			tok->value = expanded;
		}
		tok = tok->next;
	}
}
