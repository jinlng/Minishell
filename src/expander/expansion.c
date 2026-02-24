/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 19:18:58 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/24 18:03:15 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_quote_state(char c, t_quote *quote)
{
	if (c == '\'' && *quote == Q_NONE)
		*quote = Q_SINGLE;
	else if (c == '\'' && *quote == Q_SINGLE)
		*quote = Q_NONE;
	else if (c == '"' && *quote == Q_NONE)
		*quote = Q_DOUBLE;
	else if (c == '"' && *quote == Q_DOUBLE)
		*quote = Q_NONE;
}

char	*expand_string(char *str, t_env *env)
{
	int		i;
	t_quote	q;
	char	*res;

	i = 0;
	q = Q_NONE;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' && q != Q_DOUBLE)
			|| (str[i] == '"' && q != Q_SINGLE))
			update_quote_state(str[i++], &q);
		else if (str[i] == '$' && q != Q_SINGLE)
		{
			res = str_join_free(res, expand_variable(str, &i, env));
			continue ;
		}
		else
			res = char_join_free(res, str[i++]);
	}
	return (res);
}
/*char	*expand_string(char *str, t_env *env)
{
	int			i;
	t_quote		quote;
	char		*result;
	char		*tmp;

	i = 0;
	quote = Q_NONE;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"'))
		{
			if ((str[i] == '\'' && quote != Q_DOUBLE)
				|| (str[i] == '"' && quote != Q_SINGLE))
			{
				update_quote_state(str[i], &quote);
				i++;
				continue ;
			}
		}
		if (str[i] == '$' && quote != Q_SINGLE)
		{
			tmp = expand_variable(str, &i, env);
			result = str_join_free(result, tmp);
			continue ;
		}
		result = char_join_free(result, str[i]);
		i++;
	}
	return (result);
}*/

char	*expand_variable(char *str, int *i, t_env *env)
{
	int		start;
	char	*key;
	char	*value;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(g_exit_status));
	}
	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		return (ft_strdup("$"));
	start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	key = ft_substr(str, start, *i - start);
	value = get_env_value(key, env);
	free(key);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
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
			expanded = expand_string(tok->value, env);
			free(tok->value);
			tok->value = expanded;
		}
		tok = tok->next;
	}
}

void	wait_all(pid_t last_pid)
{
	int		status;
	pid_t	pid;

	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
			set_exit_status(status);
		pid = wait(&status);
	}
}
