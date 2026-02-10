/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:50:05 by potabaga          #+#    #+#             */
/*   Updated: 2025/05/06 17:04:38 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
/*
int	main()
{
	int a = 0;
	int b = 'a';
	printf("%d\n", ft_isprint(a));
	printf("%d\n", ft_isprint(b));
	return (0);
}*/
