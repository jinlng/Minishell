/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:35:45 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/12 18:45:05 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->token = NULL;
	cmd->redir = NULL;
	cmd->pipe_out = 0;
	cmd->next = NULL;
	return (cmd);
}

// void	add_redir(t_cmd *cmd, t_token *tok)
// {
// 	t_redir	*new;
// 	t_redir	*tmp;

// 	if (!tok->next || tok->next->type != WORD)
// 		return ;
// 	new = malloc(sizeof(t_redir));
// 	if (!new)
// 		return ;
// 	new->type = tok->type;
// 	new->file = ft_strdup(tok->next->value);
// 	new->quote = tok->next->quote;
// 	new->next = NULL;
// 	if (!cmd->redir)
// 		cmd->redir = new;
// 	else
// 	{
// 		tmp = cmd->redir;
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = new;
// 	}
// }

void	add_arg(t_cmd *cmd, char *arg)
{
	int		i;
	char	**new_argv;

	i = 0;
	while (cmd->argv && cmd->argv[i])
		i++;
	new_argv = malloc(sizeof(char *) * (i + 2));
	if (!new_argv)
		return ;
	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[i] = ft_strdup(arg);
	new_argv[i + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

void	add_redir(t_cmd *cmd, t_token_type type, char *file, t_quote quote)
{
	t_redir	*new;
	t_redir	*tmp;

	new = malloc(sizeof(t_redir));
	if (!new)
		return ;

	new->type = type;
	new->file = ft_strdup(file);
	new->quote = quote;
	new->next = NULL;

	if (!cmd->redir)
		cmd->redir = new;
	else
	{
		tmp = cmd->redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
