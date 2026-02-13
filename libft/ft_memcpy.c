/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:57:44 by jinliang          #+#    #+#             */
/*   Updated: 2025/04/24 18:58:58 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*psrc;
	unsigned char	*pdst;

	if (!dst && !src)
		return (NULL);
	pdst = (unsigned char *) dst;
	psrc = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		pdst[i] = psrc[i];
		i++;
	}
	return (pdst);
}
