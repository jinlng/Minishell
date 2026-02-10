/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:21:17 by potabaga          #+#    #+#             */
/*   Updated: 2025/05/21 16:21:26 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_char_in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		start;
	int		end;
	char	*result;
	int		i;

	i = 0;
	start = 0;
	end = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_char_in_set(s1[start], set))
		start++;
	end = 0;
	while (s1[end])
		end++;
	end--;
	while (end > start && ft_char_in_set(s1[end], set))
	end--;
	result = (char *)malloc(end - start + 2);
	if (!result)
		return (NULL);
	while (start <= end)
		result[i++] = s1[start++];
	result[i] = '\0';
	return (result);
}

/*int main()
{
	char *res = ft_strtrim ("/ibla ble/2i", "/2,i");
	if(res)
	{
		printf("%s\n", res);
		free(res);
	}
	return(0);
}*/