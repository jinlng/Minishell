/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:39:17 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/10 19:32:24 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(char *input)
{
	int		i;
	t_token	*tokens;
	t_quote	quote;

	i = 0;
	tokens = NULL;
	quote = Q_NONE;
	while (input[i])
	{
		if (is_whitespace(input[i]))
		{
			i++;
			continue ;
		}
		if (!input[i])
			break ;
		if (is_operator(input[i]))
			create_operator_token(&tokens, input, &i);
		else
			token_add_back(&tokens,
				new_token(WORD, extract_word(input, &i, quote), Q_NONE));
	}
	return (tokens);
}

void	*create_operator_token(t_token **tokens, char *input, int *i)
{
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		token_add_back(tokens, new_token(HEREDOC, ft_strndup("<<", 2), Q_NONE));
		*i += 2;
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		token_add_back(tokens, new_token(REDIR_APPEND, ft_strndup(">>", 2), Q_NONE));
		*i += 2;
	}
	else if (input[*i] == '|')
	{
		token_add_back(tokens, new_token(PIPE, ft_strndup("|", 1), Q_NONE));
		(*i)++;
	}
	else if (input[*i] == '<')
	{
		token_add_back(tokens, new_token(REDIR_IN, ft_strndup("<", 1), Q_NONE));
		(*i)++;
	}
	else if (input[*i] == '>')
	{
		token_add_back(tokens, new_token(REDIR_OUT, ft_strndup(">", 1), Q_NONE));
		(*i)++;
	}
}

char	*extract_word(char *s, int *i, t_quote *quote)
{
	int		start;
	char	q;

	start = *i;
	q = 0;
	*quote = Q_NONE;
	if (s[*i] == '\'' || s[*i] == '"')
	{
		q = s[*i];
		if (q == '\'')
			*quote = Q_SINGLE;
		else if (q == '"')
			*quote = Q_DOUBLE;
		start = ++(*i);
		while (s[*i] && s[*i] != q)
			(*i)++;
		return (ft_strndup(s + start, *i - start));
	}
	while (s[*i] && is_whitespace(s[*i]) && !is_operator(s[*i]))
        (*i)++;
    return ft_strndup(s + start, *i - start);
}
