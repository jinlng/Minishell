/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:12:25 by jinliang          #+#    #+#             */
/*   Updated: 2025/05/13 18:00:43 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = (char *)malloc(len);
	if (!joined)
		return (NULL);
	ft_strlcpy(joined, s1, len);
	ft_strlcat(joined, s2, len);
	return (joined);
}
