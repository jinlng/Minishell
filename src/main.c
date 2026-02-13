/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:16:36 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/13 17:58:48 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status = 0;



int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: %s \"command line\"\n", argv[0]);
        return 1;
    }
    printf("Input: %s\n", argv[1]);
    t_token *tokens = lexer(argv[1]);
    print_tokens(tokens);
    t_cmd *cmds = parser(tokens);
    print_cmds(cmds);
    return 0;
}
