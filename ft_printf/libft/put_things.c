/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_things.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:12:37 by abaur             #+#    #+#             */
/*   Updated: 2019/12/02 16:58:12 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(const char *s)
{
	if (s)
		while (*s)
			write(1, s++, 1);
}

void	ft_putendl(const char *s)
{
	if (s)
		while (*s)
			write(1, s++, 1);
	write(1, "\n", 1);
}

void	ft_putnbr(int n)
{
	char	c;

	if (n <= -10 || 10 <= n)
		ft_putnbr(n / 10);
	else if (n < 0)
		write(1, "-", 1);
	n %= 10;
	c = '0' + (n < 0 ? -n : n);
	write(1, &c, 1);
}
