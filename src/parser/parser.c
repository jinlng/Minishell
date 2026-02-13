/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:48:12 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/12 18:49:53 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parser(t_token *tok)
{
	t_cmd	*head;
	t_cmd	*cur;

	if (!tok)
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

int handle_pipe(t_cmd **cur)
{
    if (!(*cur)->argv)
        return (printf("syntax error near |"), 1);
    (*cur)->pipe_out = 1;
    (*cur)->next = init_cmd();
    *cur = (*cur)->next;
    return 0;
}

int	handle_redir(t_cmd *cur, t_token **tok)
{
	t_token_type	type;
	t_token		*file_tok;

	type = (*tok)->type;
	file_tok = (*tok)->next;

	if (!file_tok || file_tok->type != WORD)
	{
		printf("minishell: syntax error near redirection\n");
		return (1);
	}

	add_redir(cur, type, file_tok->value, file_tok->quote);

	*tok = file_tok;  // advance to file token
	return (0);
}


