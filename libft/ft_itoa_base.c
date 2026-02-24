/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:32:25 by jinliang          #+#    #+#             */
/*   Updated: 2025/08/05 15:08:56 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_num_len_base(int n, int base)
{
	int	len;

	len = (n <= 0);
	while (n)
	{
		n /= base;
		len++;
	}
	return (len);
}

char	*ft_itoa_base(int n, int base)
{
	char	*str;
	long	nb;
	int		len;

	if (base < 2 || base > 16)
		return (NULL);
	nb = n;
	len = get_num_len_base(n, base);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (len-- > (n < 0))
	{
		str[len] = "0123456789ABCDEF"[nb % base];
		nb /= base;
	}
	return (str);
}
