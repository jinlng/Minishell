/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinliang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:32:13 by jinliang          #+#    #+#             */
/*   Updated: 2025/08/05 15:05:19 by jinliang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_valid_specifier(char c)
{
	if (c == 'c' || c == 's' || c == 'p')
		return (1);
	if (c == 'd' || c == 'i' || c == 'u')
		return (1);
	if (c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

static int	handle_conversion(const char *format, int *i, va_list args)
{
	int		printed;
	char	specifier;

	printed = 0;
	*i = *i + 1;
	specifier = format[*i];
	if (specifier == '\0')
	{
		write(1, "%", 1);
		printed++;
		return (printed);
	}
	if (is_valid_specifier(specifier))
		printed = print_conversion(specifier, args);
	else
	{
		write(1, "%", 1);
		write(1, &specifier, 1);
		printed += 2;
	}
	return (printed);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		printed;

	if (!format)
		return (0);
	va_start(args, format);
	i = -1;
	printed = 0;
	while (format[++i])
	{
		if (format[i] == '%')
			printed += handle_conversion(format, &i, args);
		else
			printed += print_char(format[i]);
	}
	va_end(args);
	return (printed);
}
