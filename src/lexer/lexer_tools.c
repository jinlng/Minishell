/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:38:58 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/24 12:29:27 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_token	*new_token(t_token_type type, char *value, t_quote quote)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = value;
	new->quote = quote;
	new->next = NULL;
	return (new);
}

void	token_add_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	*create_operator_token(t_token **tokens, char *input, int *i)
{
	if (input[*i] == '|')
		token_add_back(tokens, new_token(PIPE, ft_strdup("|"), Q_NONE));
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		token_add_back(tokens, new_token(HEREDOC, ft_strdup("<<"), Q_NONE));
		(*i)++;
	}
	else if (input[*i] == '<')
		token_add_back(tokens, new_token(REDIR_IN, ft_strdup("<"), Q_NONE));
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		token_add_back(tokens, new_token(REDIR_APPEND,
				ft_strdup(">>"), Q_NONE));
		(*i)++;
	}
	else if (input[*i] == '>')
		token_add_back(tokens, new_token(REDIR_OUT, ft_strdup(">"), Q_NONE));
	(*i)++;
	return (NULL);
}
