/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:30:34 by potabaga          #+#    #+#             */
/*   Updated: 2025/05/16 16:47:18 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		while (needle[j] != '\0'
			&& haystack[i + j] != '\0'
			&& (i + j) < len
			&& haystack [i + j] == needle [j])
		{
			j++;
		}
		if (needle [j] == '\0')
			return ((char *)&haystack [i]);
		i++;
	}
	return (NULL);
}

/*
int	main()
{
	char haystack[] = "to go too foodvdsvsdvsdvsdvsdvs";
	char needle[] = "too";
	char *result;

	result = ft_strnstr(haystack, needle, 22);
	printf("Application: %s\n", result);
	return (0);
}*/
