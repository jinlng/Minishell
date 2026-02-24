/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:52:28 by jinliang          #+#    #+#             */
/*   Updated: 2025/05/15 13:37:07 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dst;
	size_t	dst_len;

	dst_len = ft_strlen(s) + 1;
	dst = (char *) ft_calloc(dst_len, 1);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s, dst_len);
	return (dst);
}
