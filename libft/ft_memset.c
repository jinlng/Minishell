/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <potabaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:05:58 by potabaga          #+#    #+#             */
/*   Updated: 2026/01/14 14:35:41 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int v, size_t count)
{
	size_t					i;
	unsigned char			*ptr;

	ptr = (unsigned char *) dest;
	i = 0;
	while (i < count)
	{
		ptr[i] = (unsigned char) v;
		i++;
	}
	return (dest);
}

/*int	 main()
{
	char b[] = "hello, h!";
//	char c[] = "hello";
	ft_memset(b, '*', 5);
	//ft_memset(c + 4, '-', 4);
	printf("%s\n", b);
//	printf("%s\n", c);
	return (0);
}*/
