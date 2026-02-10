/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:38:59 by potabaga          #+#    #+#             */
/*   Updated: 2025/05/21 10:33:59 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;

	ptr = (const unsigned char *)s;
	while (n-- > 0)
	{
		if (*ptr == (unsigned char) c)
		{
			return ((void *)ptr);
		}
		ptr++;
	}
	return (NULL);
}
/*
int 	main()
{
	char a[] = "blabla";
	char *result = ft_memchr(a, 'x', 5);
	if (result != NULL)
		printf("symbole: %c\n", *result);
	else
		printf("Pas de symbole\n");
	return (0);
}*/
