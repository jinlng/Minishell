/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:44:47 by jinliang          #+#    #+#             */
/*   Updated: 2025/08/05 15:06:50 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_ptr(void *ptr)
{
	unsigned long	addr;
	int				len;
	char			*str;

	if (!ptr)
		return (write(1, "(nil)", 5));
	addr = (unsigned long)ptr;
	len = 0;
	str = ft_utoa_base(addr, 16, 0);
	len += write(1, "0x", 2);
	len += write(1, str, ft_strlen(str));
	free(str);
	return (len);
}
