/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:39:17 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/09 17:01:17 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(char *input)
{
	int		i;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		if (is_whitespace(input[i]))
			i++;
		else if (input[i] == '|')
			token_add_back(&tokens, new_token(PIPE, strndup("|", 1))), i++;
		else if (input[i] == '<')
			token_add_back(&tokens, new_token(REDIR_IN, strndup("<", 1))), i++;
		else if (input[i] == '>')
			token_add_back(&tokens, new_token(REDIR_OUT, strndup(">", 1))), i++;
		else if (input[i] == '<' && input[i + 1] == '<')
			token_add_back(&tokens, new_token(HEREDOC, strndup("<<", 2))), i += 2;
		else if (input[i] == '>' && input[i + 1] == '>')
			token_add_back(&tokens, new_token(REDIR_APPEND, strndup(">>", 2))), i += 2;
		else
			token_add_back(&tokens, new_token(WORD, extract_word(input, &i)));
	}
	return (tokens);
}

char	*extract_word(char *str, int *i)
{
	int		start;
	char	quote;

	start = *i;
	quote = 0;
	while (str[*i])
	{
		if (!quote && (is_whitespace(str[*i]) || is_special(str[*i])))
			break;
		if (str[*i] == '\'' || str[*i] == '"')
		{
			quote = str[*i];
			(*i)++;
			start = *i;
			while (str[*i] && str[*i] != quote)
				(*i)++;
		}
		(*i)++;
	}
	return (strndup(str + start, *i - start));
}
