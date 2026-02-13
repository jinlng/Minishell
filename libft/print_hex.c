/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:47:57 by jinliang          #+#    #+#             */
/*   Updated: 2025/08/05 15:08:50 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_hex(unsigned int n, int uppercase)
{
	char	*str;
	int		len;

	str = ft_utoa_base(n, 16, uppercase);
	len = ft_strlen(str);
	write(1, str, len);
	free(str);
	return (len);
}
