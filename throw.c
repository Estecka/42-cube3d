/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:12:54 by abaur             #+#    #+#             */
/*   Updated: 2020/01/22 12:56:55 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "throw.h"

#include <stdlib.h>
#include "libft/libft.h"
#include "ft_printf/ft_printf.h"

void	vthrow(int status, char *errformat, va_list args)
{
	ft_putstr("Error\n");
	ft_putstr("Status code: ");
	ft_putnbr(status);
	ft_putchar('\n');
	ft_vprintf(errformat, args);
	ft_putchar('\n');
	va_end(args);
	exit(status);
}

void	throwif(short condition, int status, char *errformat, ...)
{
	va_list args;

	if (condition)
	{
		va_start(args, errformat);
		vthrow(status, errformat, args);
	}
}

void	throw(int status, char *errformat, ...)
{
	va_list args;

	va_start(args, errformat);
	vthrow(status, errformat, args);
}
