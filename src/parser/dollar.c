/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:14:10 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/09 17:01:11 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_dollar(char *str, int last_status)
{
    char *res = malloc(1);
    int i = 0;

    res[0] = '\0';
    while (str[i])
    {
        if (str[i] == '$')
        {
            i++;
            if (str[i] == '?')
            {
                res = ft_strjoin_free(res, ft_itoa(last_status));
                i++;
            }
            else
            {
                char name[256];
                int j = 0;
                while (ft_isalnum(str[i]) || str[i] == '_')
                    name[j++] = str[i++];
                name[j] = '\0';
                if (getenv(name))
                    res = ft_strjoin_free(res, getenv(name));
            }
        }
        else
            res = ft_charjoin(res, str[i++]);
    }
    return (res);
}
