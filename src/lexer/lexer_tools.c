/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:38:58 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/09 17:01:16 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_whitespace(char c)
{
    return (c == ' ' || c == '\t');
}

int is_special(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

t_token *new_token(t_token_type type, char *value)
{
    t_token *tok = malloc(sizeof(t_token));
    if (!tok)
        return (NULL);
    tok->type = type;
    tok->value = value;
    tok->next = NULL;
    return (tok);
}

void token_add_back(t_token **lst, t_token *new)
{
    t_token *tmp;

    if (!*lst)
    {
        *lst = new;
        return;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
