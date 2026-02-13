/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:16:36 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/13 19:36:15 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status = 0;

// int	main(int argc, char **argv)
// {
// 	if (argc < 2)
// 	{
// 		printf("Usage: %s \"command line\"\n", argv[0]);
// 		return 1;
// 	}
// 	printf("Input: %s\n", argv[1]);
// 	t_token *tokens = lexer(argv[1]);
// 	print_tokens(tokens);
// 	t_cmd *cmds = parser(tokens);
// 	print_cmds(cmds);
// 	return 0;
// }

int main(int argc, char **argv, char **envp)
{
    char *line;
    t_env env;

    (void)argc;
    (void)argv;

    init_env(&env, envp);       // 初始化环境链表
    setup_signals();            // 设置 ctrl-C/ctrl-\ 等信号

    while (1)
    {
        line = readline("minishell$ "); // 读用户输入
        if (!line)                        // Ctrl-D
            break;

        if (*line) // 忽略空行
        {
            add_history(line);          // 历史记录
            execute_line(line, &env);   // lexer->parser->expand->execute
        }
        free(line);
    }

    free_all_global(&env);
    return (g_exit_status);
}


void execute_line(char *line, t_env *env)
{
    t_token *tokens;
    t_cmd *cmds;

    tokens = lexer(line);
    expand_tokens(tokens, env);
    cmds = parser(tokens);
    execute(cmds, env);

    free_tokens(tokens);
    free_cmd(cmds);
}
