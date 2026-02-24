/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:16:36 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/24 22:45:35 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

/*void	process_command_line(char *line, t_env *env)
{
	t_token	*tokens;
	t_cmd	*cmds;

	if (!line || !*line)
		return ;
	tokens = lexer(line);
	if (!tokens)
		return ;
	expand_tokens(tokens, env);
	cmds = parser(tokens);
	if (!cmds)
	{
		g_exit_status = 2;
		free_tokens(tokens);
		return ;
	}
	if (process_heredocs(cmds))
	{
		if (g_exit_status == 0)
			g_exit_status = 1;
		free_tokens(tokens);
		free_cmd(cmds);
		return ;
	}
	execute(cmds, env);
	free_tokens(tokens);
	free_cmd(cmds);
}*/

void	process_command_line(char *line, t_env *env)
{
	t_token	*tokens;
	t_cmd	*cmds;

	if (!line || !*line)
		return ;
	tokens = lexer(line);
	if (!tokens)
		return ;
	expand_tokens(tokens, env);
	cmds = parser(tokens);
	if (!cmds)
		g_exit_status = 2;
	else if (process_heredocs(cmds))
	{
		if (g_exit_status == 0)
			g_exit_status = 1;
	}
	else
		execute(cmds, env);
	free_tokens(tokens);
	if (cmds)
		free_cmd(cmds);
}

/*void	minishell_loop(t_env *env)
{
	char	*line;
	size_t	len;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			line = readline(create_prompt(env));
			if (line && *line)
				add_history(line);
		}
		else
		{
			line = get_next_line(STDERR_FILENO);
			if (line)
			{
				len = ft_strlen(line);
				if (len > 0 && line[len - 1] == '\n')
				line[len - 1] = '\0';
			}
		}
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				ft_putstr_fd("exit\n", 1);
			break ;
		}
		process_command_line(line, env);
		free(line);
	}
}*/
void	minishell_loop(t_env *env)
{
	char	*line;
	char	*prompt;
	size_t	len;

	while (1)
	{
		prompt = create_prompt(env);
		if (isatty(STDIN_FILENO))
			line = readline(prompt);
		else
			line = get_next_line(STDIN_FILENO);
		free(prompt);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (*line && isatty(STDIN_FILENO))
			add_history(line);
		process_command_line(line, env);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	if (!env)
		return (1);
	set_parent_signals();
	minishell_loop(env);
	free_env(&env);
	clear_history();
	return (g_exit_status);
}
