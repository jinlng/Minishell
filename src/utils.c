/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:59:26 by potabaga          #+#    #+#             */
/*   Updated: 2026/01/28 13:43:55 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

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

char	**split_args(char **args, int start, int end)
{
	int		i;
	char	**out;

	out = malloc(sizeof(char *) * (end - start + 1));
	i = 0;
	while (start < end)
	{
		out[i++] = ft_strdup(args[start]);
		start++;
	}
	out[i] = NULL;
	return (out);
}

int	count_cmds(char **args)
{
	int	i = 0;
	int	count = 1;

	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
			count++;
		i++;
	}
	return (count);
}

char	***split_pipeline(char **args, int count)
{
	char	***cmds;
	int		i;
	int		start;
	int		j;

	cmds = malloc(sizeof(char **) * (count + 1));
	i = 0;
	start = 0;
	j = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
		{
			cmds[j++] = split_args(args, start, i);
			start = i + 1;
		}
		i++;
	}
	cmds[j++] = split_args(args, start, i);
	cmds[j] = NULL;
	return (cmds);
}
