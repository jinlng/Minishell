/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:38:58 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/10 17:42:25 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
    return (c == ' ' || c == '\t');
}

int	is_operator(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

t_token	*new_token(t_token_type type, char *value, t_quote quote)
{
    t_token *t;

	t = malloc(sizeof(t_token));
    if (!t)
        return (NULL);
    t->type = type;
    t->value = value;
	t->quote = quote;
    t->next = NULL;
    return (t);
}

void	token_add_back(t_token **lst, t_token *new)
{
    t_token *tmp;

    if (!*lst)
    {
        *lst = new;
        return ;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
