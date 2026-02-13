/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:26:04 by jinliang          #+#    #+#             */
/*   Updated: 2025/08/05 15:58:54 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_words(const char *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static size_t	len_word(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static void	free_all(char **arr, size_t n)
{
	while (n--)
		free(arr[n]);
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	i;
	size_t	len;
	size_t	n_words;

	if (!s)
		return (NULL);
	n_words = count_words(s, c);
	res = malloc(sizeof(char *) * (n_words + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < n_words)
	{
		while (*s && *s == c)
			s++;
		len = len_word(s, c);
		res[i] = ft_substr(s, 0, len);
		if (!res[i])
			return (free_all(res, i), NULL);
		s += len;
		i++;
	}
	res[i] = NULL;
	return (res);
}
