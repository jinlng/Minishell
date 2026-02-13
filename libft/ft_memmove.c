/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:59:07 by jinliang          #+#    #+#             */
/*   Updated: 2025/05/12 13:06:29 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*psrc;
	unsigned char	*pdst;

	if (!dst && !src)
		return (NULL);
	pdst = (unsigned char *) dst;
	psrc = (unsigned char *) src;
	if (dst > src)
	{
		while (n > 0)
		{
			pdst[n - 1] = psrc[n - 1];
			n--;
		}
	}
	else
		ft_memcpy(pdst, psrc, n);
	return (pdst);
}
