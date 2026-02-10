/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:20:49 by potabaga          #+#    #+#             */
/*   Updated: 2025/05/20 17:21:25 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last = NULL;

	while (*s)
	{
		if (*s == (char)c)
			last = s;
		s++;
	}
	if (*s == (char) c)
		last = s;
	return ((char *) last);
}
/*
int	main()
{	
	char buf[] = "campus campus";
	char *ptr;
	int c = 'm';
	ptr = ft_strrchr(buf, c);
	printf("last occurence of %c in '%s' is '%s'\n", c, buf, ptr);
	return (0);
}*/
