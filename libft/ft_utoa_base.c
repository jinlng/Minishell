/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:01:09 by jinliang          #+#    #+#             */
/*   Updated: 2025/08/05 15:09:15 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_num_len_base(unsigned long n, int base)
{
	int	len;

	len = 1;
	while (n >= (unsigned long)base)
	{
		n /= base;
		len++;
	}
	return (len);
}

char	*ft_utoa_base(unsigned long n, int base, int uppercase)
{
	char	*str;
	char	*digits;
	int		len;

	if (base < 2 || base > 16)
		return (NULL);
	if (uppercase)
		digits = "0123456789ABCDEF";
	else
		digits = "0123456789abcdef";
	len = get_num_len_base(n, base);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = digits[n % base];
		n /= base;
	}
	return (str);
}
