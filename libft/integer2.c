/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:42:08 by abaur             #+#    #+#             */
/*   Updated: 2019/11/06 11:05:13 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** allocates and returns a string representing the given integer.
*/

int		ft_atoi(const char *str)
{
	return (ft_atoi_base(str, "0123456789"));
}

char	*ft_itoa(int n)
{
	return (ft_itoa_base(n, "0123456789"));
}
