/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:43:52 by potabaga          #+#    #+#             */
/*   Updated: 2025/05/21 10:38:16 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	i = 0;
	while (src[i])
	i++;
	return (i);
}

/*int main()
{	
	char dst[] = "blabla";
	char src[] = "***";
	int size = 6;
	int result;
	result = ft_strlcpy(dst, src, size);
	printf("%s\n", result);
	return (0);
}*/
