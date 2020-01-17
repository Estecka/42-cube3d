/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:50:25 by abaur             #+#    #+#             */
/*   Updated: 2019/12/03 12:01:45 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

/*
** Prints the arguments formatted with the given string.
** Returns the amount of characters printed.
*/

int			ft_vprintf(const char *format, va_list args)
{
	int			result;
	t_pftag		tag;

	if (!format)
		return (0);
	result = 0;
	while (*format)
		if (*format == '%')
		{
			if (*++format)
			{
				parsetag(&format, &tag, args);
				result += tag.writer(&tag);
				if (tag.buffer)
					free(tag.buffer);
				tag.buffer = NULL;
			}
		}
		else
		{
			write(1, format++, 1);
			result += 1;
		}
	return (result);
}

int			ft_printf(const char *format, ...)
{
	va_list	args;
	int		result;

	va_start(args, format);
	result = ft_vprintf(format, args);
	va_end(args);
	return (result);
}
