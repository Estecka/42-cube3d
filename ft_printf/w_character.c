/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_character.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:11:40 by abaur             #+#    #+#             */
/*   Updated: 2019/12/03 11:39:01 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

int	w_character(t_pftag *tag)
{
	char	arg;
	int		result;

	result = 0;
	arg = (char)tag->argument;
	result += tag->printer(tag->buffer, arg);
	result += flushbuffer(tag->buffer);
	return (result);
}
