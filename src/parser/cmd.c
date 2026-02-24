/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:35:45 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/23 21:00:18 by potabaga         ###   ########.fr       */
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

int	handle_pipe(t_cmd **cur)
{
	if (!(*cur)->argv)
		return (printf("syntax error near |"), 1);
	(*cur)->next = init_cmd();
	*cur = (*cur)->next;
	return (0);
}

int	handle_redir(t_cmd *cur, t_token **tok)
{
	t_token_type	type;
	t_token			*file_tok;

	type = (*tok)->type;
	file_tok = (*tok)->next;
	if (!file_tok || file_tok->type != WORD)
	{
		printf("minishell: syntax error near redirection\n");
		return (1);
	}
	add_redir(cur, type, file_tok->value, file_tok->quote);
	*tok = file_tok;
	return (0);
}
