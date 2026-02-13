/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:36:13 by jinliang          #+#    #+#             */
/*   Updated: 2025/04/28 16:35:01 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			i;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (i < n)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
#include <stddef.h>

int	main(void)
{
	char s1[] = {1, 2, 3, 4};
	char s2[] = {1, 2, 4, 3};
	printf("Test 1: %d\n", ft_memcmp(s1, s2, 4));
	printf("Test 4: %d\n", ft_memcmp(s1, s2, 0));
	return (0);
}*/
