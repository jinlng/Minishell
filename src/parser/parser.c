/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:48:12 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/24 16:29:48 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parser(t_token *tok)
{
	t_cmd	*head;
	t_cmd	*cur;

	if (!tok || !check_syntax(tok))
		return (NULL);
	head = init_cmd();
	cur = head;
	while (tok)
	{
		if (tok->type == PIPE)
		{
			if (handle_pipe(&cur))
				return (NULL);
		}
		else if (tok->type == WORD)
			add_arg(cur, tok->value);
		else
		{
			if (handle_redir(cur, &tok))
				return (NULL);
		}
		tok = tok->next;
	}
	return (head);
}

int	check_syntax(t_token *tok)
{
	t_token	*prev;
	int		has_cmd;

	if (tok && tok->type == PIPE)
		return (syntax_error("|"));
	prev = NULL;
	has_cmd = 0;
	while (tok)
	{
		if (is_redir(tok->type) && (!tok->next || tok->next->type != WORD))
			return (syntax_error("newline"));
		if (tok->type == PIPE)
		{
			if (!has_cmd || !tok->next || tok->next->type == PIPE)
				return (syntax_error("|"));
			has_cmd = 0;
		}
		if (tok->type == WORD)
			has_cmd = 1;
		prev = tok;
		tok = tok->next;
	}
	if (!has_cmd || (prev && is_redir(prev->type)))
		return (syntax_error("newline"));
	return (1);
}

t_token	*get_last_token(t_token *tok)
{
	if (!tok)
		return (NULL);
	while (tok->next)
		tok = tok->next;
	return (tok);
}

/*int	check_syntax(t_token *tok)
{
	t_token		*prev;
	int			has_command;

	if (!tok)
		return (0);
	else if (tok->type == PIPE)
		return (syntax_error("|"));
	prev = NULL;
	has_command = 0;
	while (tok)
	{
		if (tok->type == PIPE && prev && prev->type == PIPE)
			return (syntax_error("|"));
		if (is_redir(tok->type))
		{
			if (!tok->next || tok->next->type != WORD)
				return (syntax_error("newline"));
		}
		if (tok->type == WORD)
		{
			if (!prev || !is_redir(prev->type))
			has_command = 1;
		}
		if (tok->type == PIPE)
		{
			if (!has_command)
				return (syntax_error("|"));
			has_command = 0;
		}
		prev = tok;
		tok = tok->next;
	}
	if ((prev && prev->type == PIPE) || !has_command)
		return (syntax_error("newline"));
	return (1);
}*/

// int	check_syntax(t_token *tok)
// {
//     // 检查空管道: | 或 || 或 | |
//     if (tok->type == PIPE)
//     {
//         if (!tok->next || tok->next->type == PIPE)
//             return (0);
//     }
//     // 检查管道后没有命令: echo |
//     t_token *last = get_last_token(tok);
//     if (last->type == PIPE)
//         return (0);   
//     return (1);
// }
