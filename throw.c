/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:12:54 by abaur             #+#    #+#             */
/*   Updated: 2020/01/22 11:28:12 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "throw.h"

#include <stdlib.h>
#include "libft/libft.h"
#include "ft_printf/ft_printf.h"

void	throwv(int status, char *errformat, va_list args)
{
	ft_putstr("Error\n");
	ft_vprintf(errformat, args);
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