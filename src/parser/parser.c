/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:48:12 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/09 17:00:59 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *parser(t_token *tokens)
{
    t_cmd   *cmds = NULL;
    t_cmd   *current = NULL;

    while (tokens)
    {
        if (!current)
        {
            current = new_cmd();
            cmd_add_back(&cmds, current);
        }
        if (tokens->type == WORD)
            add_arg(current, tokens->value);
        else if (tokens->type == PIPE)
            current = NULL;
        else if (tokens->type >= REDIR_IN && tokens->type <= HEREDOC)
        {
            t_redir_type type = tokens->type;
            tokens = tokens->next;
            if (tokens && tokens->type == WORD)
                add_redir(current, type, tokens->value);
        }
        tokens = tokens->next;
    }
    return (cmds);
}
