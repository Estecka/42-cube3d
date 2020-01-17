/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_string.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:17:57 by abaur             #+#    #+#             */
/*   Updated: 2019/12/03 11:45:50 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

int	w_string(t_pftag *tag)
{
	char	*arg;
	int		count;
	int		i;

	count = 0;
	i = 0;
	arg = (char*)tag->argument;
	if (!arg)
		arg = "(null)";
	while (*arg && (tag->precision < 0 || i++ < tag->precision))
	{
		count += tag->printer(tag->buffer, *arg);
		arg++;
	}
	count += flushbuffer(tag->buffer);
	return (count);
}
