/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:34:25 by potabaga          #+#    #+#             */
/*   Updated: 2026/02/11 18:36:30 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env	env;
// 	char	*line;

// 	(void)argc;
// 	(void)argv;
// 	env.last_status = 0;
// 	env.env = NULL;
// 	rl_catch_signals = 0;
// 	init_env(&env, envp);
// 	set_parent_signals();
// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		if (!line)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		if (*line)
// 			process_line(line, &env);
// 		free(line);
// 	}
// 	return (0);
// }

/*int	main(int argc, char **argv, char **envp)
{
	char	*line;
	
	(void)argc;
	(void)argv;

	rl_catch_signals = 0;
	init_env(envp);
	
	while (1)
	{
		set_parent_signals();
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;		
		}
		if (*line)
			process_line(line);
		free(line);
	}
}*/

pid_t g_signal_pid = 0;

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
