/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:04:48 by potabaga          #+#    #+#             */
/*   Updated: 2025/05/20 17:19:49 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char) c)
		return ((char *)s);
	return (NULL);
}

/*int	 main()
{
	char buf[] = "blablabla";
	char *ptr;
	int c = 'a';

	ptr = ft_strchr(buf, c);
	printf("the first occurence of %c in '%s' is %s\n", c, buf, ptr);
	return (0);
}*/
