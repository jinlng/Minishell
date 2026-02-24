/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:09:49 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/24 17:27:03 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_prompt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}

char	*create_prompt(t_env *env)
{
	char	*prompt;
	char	*cwd;
	char	*user;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup("minishell$ "));
	user = get_env_value("USER", env);
	if (user)
		prompt = ft_strjoin(user, "@minishell:");
	else
		prompt = ft_strdup("minishell:");
	free(user);
	tmp = prompt;
	prompt = ft_strjoin(tmp, cwd);
	free(tmp);
	tmp = prompt;
	prompt = ft_strjoin(tmp, "$ ");
	free(tmp);
	free(cwd);
	return (prompt);
}

char	*read_line_with_prompt(t_env *env)
{
	char	*prompt;
	char	*line;

	if (g_exit_status == SIGINT)
	{
		g_exit_status = 0;
		set_env_value("?", "130", &env);
	}
	prompt = create_prompt(env);
	line = readline(prompt);
	free(prompt);
	return (line);
}
