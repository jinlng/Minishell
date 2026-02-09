/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:35:45 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/09 17:01:05 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *new_cmd(void)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->argv = NULL;
    cmd->redirs = NULL;
    cmd->next = NULL;
    return (cmd);
}

void cmd_add_back(t_cmd **lst, t_cmd *new)
{
    t_cmd *tmp;

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

void add_arg(t_cmd *cmd, char *arg)
{
    int i = 0;

    while (cmd->argv && cmd->argv[i])
        i++;
    cmd->argv = realloc(cmd->argv, sizeof(char *) * (i + 2));
    cmd->argv[i] = arg;
    cmd->argv[i + 1] = NULL;
}

void add_redir(t_cmd *cmd, t_redir_type type, char *file)
{
    t_redir *redir = malloc(sizeof(t_redir));
    t_redir *tmp;

    redir->type = type;
    redir->file = file;
    redir->next = NULL;
    if (!cmd->redirs)
    {
        cmd->redirs = redir;
        return;
    }
    tmp = cmd->redirs;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = redir;
}
