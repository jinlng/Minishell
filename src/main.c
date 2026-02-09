/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:34:25 by potabaga          #+#    #+#             */
/*   Updated: 2026/02/08 18:06:00 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	env;
	char	*line;

	(void)argc;
	(void)argv;
	env.last_status = 0;
	env.env = NULL;
	rl_catch_signals = 0;
	init_env(&env, envp);
	set_parent_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			process_line(line, &env);
		free(line);
	}
	return (0);
}

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