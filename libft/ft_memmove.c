/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:18:09 by potabaga          #+#    #+#             */
/*   Updated: 2025/05/21 10:23:13 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t size)
{
	size_t					i;
	unsigned char			*d;
	const unsigned char		*s;

	d = (unsigned char *) dst;
	s = (const unsigned char *) src;
	if (dst == src || size == 0)
		return (dst);
	if (d > s)
	{
		while (size--)
		{
			d[size] = s[size];
		}
	}
	else
	{
		i = 0;
		while (i < size)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}
/*
int	main()
{
	char buf[] = "blabla";
	ft_memmove(buf + 3, buf, 5);
	printf("%s\n",buf);
	return (0);
}*/
