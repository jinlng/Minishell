/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:33:46 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/13 19:02:54 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* builtin_unset */
int	builtin_unset(char **argv, t_env **env)
{
	t_env	*cur;
	t_env	*prev;
	int		i;

	g_exit_status = 0;
	if (!argv[1])
		return (0);

	i = 1;
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_exit_status = 1;
			i++;
			continue ;
		}

		cur = *env;
		prev = NULL;

		while (cur)
		{
			if (ft_strcmp(cur->key, argv[i]) == 0)
			{
				if (prev)
					prev->next = cur->next;
				else
					*env = cur->next; // 删除头节点
				free(cur->key);
				free(cur->value);
				free(cur);
				break ;
			}
			prev = cur;
			cur = cur->next;
		}
		i++;
	}
	return (g_exit_status);
}

