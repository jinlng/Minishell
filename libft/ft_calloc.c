/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potabaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:15:35 by potabaga          #+#    #+#             */
/*   Updated: 2025/05/20 15:50:34 by potabaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t m)
{
	void	*ptr;

	ptr = malloc (n * m);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, n * m);
	return (ptr);
}
/*
int	main()
{
	int *arr;
	int i = 0;
	arr = (int *)ft_calloc(5, sizeof(int));
	if (arr == NULL)
	{
		printf("Erreur\n");
		return (1);
	}
	while (i < 5)
	{
		printf("arr[%d] = %d\n", i, arr[i]);
		i++;
	}
	free(arr);
	return (0);
*/
