/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:43:57 by potabaga          #+#    #+#             */
/*   Updated: 2025/05/22 14:43:59 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	word_count(const char *s, char c)
{
	size_t	count;
	int		in_word;

	in_word = 0;
	count = 0;
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

static void	free_words(char **res, size_t j)
{
	while (j > 0)
	{
		j--;
		free(res[j]);
	}
	free(res);
}

static char	*word_dup(const char *s, size_t start, size_t end)
{
	char	*word;
	size_t	i;

	word = malloc(end - start + 1);
	i = 0;
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

char	**arr_res(char **res, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			res[j] = word_dup(s, start, i);
			if (!res[j++])
			{
				free_words (res, j - 1);
				return (NULL);
			}
		}
	}
	res[j] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**final_res;

	if (!s)
		return (NULL);
	final_res = (char **)malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!final_res)
		return (NULL);
	if (!arr_res(final_res, s, c))
		return (NULL);
	return (final_res);
}

/* int main()
{
	char *s = "\0aa\0bbb";
	char c = '\0';
	ft_split(s, c);
	// printf("%s\n", ft_split(s, c)[0]);
	// printf("%s\n", ft_split(s, c)[1]);
	//printf("%s\n", ft_split(s, c/)[2]);
	//printf("%s\n", ft_split(s, c)[3]);
	//printf("%s\n", ft_split(s, c)[4]);
	return (0);
} */