/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_things_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:12:37 by abaur             #+#    #+#             */
/*   Updated: 2019/12/02 16:56:25 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(const char *s, int fd)
{
	if (s)
		while (*s)
			write(fd, s++, 1);
}

void	ft_putendl_fd(const char *s, int fd)
{
	if (s)
		while (*s)
			write(fd, s++, 1);
	write(fd, "\n", 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n <= -10 || 10 <= n)
		ft_putnbr_fd(n / 10, fd);
	else if (n < 0)
		write(fd, "-", 1);
	n %= 10;
	c = '0' + (n < 0 ? -n : n);
	write(fd, &c, 1);
}
