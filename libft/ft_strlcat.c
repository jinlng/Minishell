/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:06:32 by potabaga          #+#    #+#             */
/*   Updated: 2025/05/16 18:22:43 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			i;
	size_t			y;
	unsigned int	result;

	i = 0;
	y = 0;
	result = 0;
	while (dst[i] != '\0')
		i++;
	while (src[result] != '\0')
		result++;
	if (size <= i)
		result = result + size ;
	else
		result = result + i;
	while (src[y] != '\0' && (i + 1) < size)
	{
		dst[i] = src[y];
		i++;
		y++;
	}
	if (size > 0)
	dst[i] = '\0';
	return (result);
}

/*int main()
{
	char dst[] = "amour";
	char src[] = "pour la vie";
	int size = 5;
	printf("%d\n", ft_strlcat(dst, src, size));
	return (0);
}*/
