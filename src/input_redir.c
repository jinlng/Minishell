/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:34:16 by potabaga          #+#    #+#             */
/*   Updated: 2026/02/08 17:41:35 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	has_input(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "<") == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	apply_input_redir(char **args)
{
	int	i;
	int	fd;
	int	save_stdin;

	i = has_input(args);
	if (i == -1)
		return (-1);
	if (!args[i + 1])
		return (printf("minishell: syntax error\n"), -2);

	fd = open(args[i + 1], O_RDONLY);
	if (fd < 0)
		return (perror("open"), -2);

	save_stdin = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	args[i] = NULL;
	return (save_stdin);
}

void	restore_stdin(int save_stdin)
{
	if (save_stdin >= 0)
	{
		dup2(save_stdin, STDIN_FILENO);
		close(save_stdin);
	}
}

void	builtin_exit(char **args, t_env *env)
{
	long	status;
	int		i;

	printf("exit\n");

	if (!args[1])
	{
        printf("exit\n");
        exit(env->last_status);
    }
	i = 0;
	while (args[1][i])
	{
		if ((args[1][i] < '0' || args[1][i] > '9')
			&& !(i == 0 && (args[1][i] == '+' || args[1][i] == '-')))
		{
			printf("minishell: exit: %s: numeric argument required\n", args[1]);
			exit(255);
		}
		i++;
	}
if (args[2])
    {
        printf("exit\nminishell: exit: too many arguments\n");
        env->last_status = 1; 
        return ;
    }
    status = ft_atol(args[1]);
    printf("exit\n");
    exit((unsigned char)status);
}
