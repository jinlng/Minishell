/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:39:17 by jinliang          #+#    #+#             */
/*   Updated: 2026/02/24 12:26:38 by potabaga         ###   ########.fr       */
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
	char	q;

	start = *i;
	*quote = Q_NONE;
	while (s[*i] && !is_whitespace(s[*i]) && !is_operator(s[*i]))
	{
		if ((s[*i] == '\'' || s[*i] == '"'))
		{
			q = s[*i];
			(*i)++;
			while (s[*i] && s[*i] != q)
				(*i)++;
			if (s[*i] == q)
				(*i)++;
		}
		else
			(*i)++;
	}
	return (ft_substr(s, start, *i - start));
}

// char *extract_word(char *s, int *i, t_quote *quote)
// {
//     int start;
//     int len;

//     start = *i;
//     *quote = Q_NONE;

//     while (s[*i] && !is_whitespace(s[*i]) && !is_operator(s[*i]))
//     {
//         if (s[*i] == '\'' || s[*i] == '"')
//         {
//             *quote = (s[*i] == '\'') ? Q_SINGLE  : Q_DOUBLE;
//             (*i)++;
//             while (s[*i] && s[*i] != '\'' && s[*i] != '"')
//                 (*i)++;
//         }
//         (*i)++;
//     }

//     len = *i - start;

//     return build_word_without_quotes(&s[start], len, *quote);
// }

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
