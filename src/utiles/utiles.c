/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 16:56:03 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/13 19:06:33 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_numeric(char *s)
{
    int i = 0;

    if (!s || !s[0])
        return 0;

    if (s[0] == '-' || s[0] == '+')
        i++;

    while (s[i])
    {
        if (!ft_isdigit(s[i]))
            return 0;
        i++;
    }

    return 1;
}

void print_tokens(t_token *tok)
{
    printf("Tokens:\n");
    while (tok)
    {
        printf("  Type: %d, Value: [%s], Quote: %d\n", tok->type, tok->value, tok->quote);
        tok = tok->next;
    }
}

void print_cmds(t_cmd *cmd)
{
    int i;
    printf("Commands:\n");
    while (cmd)
    {
        printf("  Args: ");
        if (cmd->argv)
        {
            for (i = 0; cmd->argv[i]; i++)
                printf("[%s] ", cmd->argv[i]);
        }
        printf("\n  Redirs: ");
        t_redir *r = cmd->redir;
        while (r)
        {
            printf("{Type: %d, File: %s} ", r->type, r->file);
            r = r->next;
        }
        printf("\n  Pipe Out: %d\n", cmd->pipe_out);
        printf("  ---\n");
        cmd = cmd->next;
    }
}
