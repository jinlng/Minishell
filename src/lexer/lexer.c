/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:39:17 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/11 19:21:34 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(char *input)
{
	t_token	*tokens;
	int		i;
	char	*word;
	t_quote	quote;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && is_whitespace(input[i]))
			i++;
		if (!input[i])
			break ;
		if (is_operator(input[i]))
			create_operator_token(&tokens, input, &i);
		else
		{
			word = extract_word(input, &i, &quote);
			token_add_back(&tokens, new_token(WORD, word, quote));
		}
	}
	return (tokens);
}

char	*extract_word(char *s, int *i, t_quote *quote)
{
	int		start;
	char	q_char;

	start = *i;
	*quote = Q_NONE;
	if (s[*i] == '\'' || s[*i] == '\"')
	{
		q_char = s[*i];
		*quote = (q_char == '\'') ? Q_SINGLE : Q_DOUBLE;
		(*i)++;
		start = *i;
		while (s[*i] && s[*i] != q_char)
			(*i)++;
		char *word = ft_substr(s, start, *i - start);
		if (s[*i] == q_char)
			(*i)++;
		return (word);
	}
	while (s[*i] && !is_whitespace(s[*i]) && !is_operator(s[*i]))
		(*i)++;
	return (ft_substr(s, start, *i - start));
}


// char	*build_word_without_quotes(char *src, int len, t_quote quote)
// {
// 	int		i;
// 	int		j;
// 	char	*dst;

// 	i = -1;
// 	j = 0;
// 	dst = malloc(len + 1);
// 	if (!dst)
// 		return (NULL);
// 	while (++i < len)
// 	{
// 		if (quote == Q_NONE && src[i] == '\'')
// 			quote = Q_SINGLE;
// 		else if (quote == Q_NONE && src[i] == '"')
// 			quote = Q_DOUBLE;
// 		else if (quote == Q_SINGLE && src[i] == '\'')
// 			quote = Q_NONE;
// 		else if (quote == Q_DOUBLE && src[i] == '"')
// 			quote = Q_NONE;
// 		else
// 			dst[j++] = src[i];
// 	}
// 	dst[j] = '\0';
// 	return (dst);
// }
