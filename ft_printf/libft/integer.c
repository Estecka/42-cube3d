/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:32:09 by abaur             #+#    #+#             */
/*   Updated: 2019/11/18 12:17:15 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			indexof(char c, const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

static int	base_size(const char *base)
{
	int		i;

	i = -1;
	while (base[++i])
		if (ft_strcontain("\t\n\r\v\f +-", base[i])
			|| ft_strcontain(&base[i + 1], base[i]))
			return (0);
	return ((i < 2) ? 0 : i);
}

int			ft_atoi_base(const char *str, const char *base)
{
	short	sign;
	int		dozen;
	int		result;
	int		digit;

	if (!(dozen = base_size(base)))
		return (0);
	while (ft_strcontain("\t\n\r\v\f ", *str))
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign *= -1;
	result = 0;
	while (*str)
	{
		digit = indexof(*str, base);
		if (digit < 0)
			return (result);
		result *= dozen;
		result += digit * sign;
		str++;
	}
	return (result);
}

/*
** This writes an integer into a string recursively.
** The first iteration writes the last number, it finds the pointer to the last
** character by asking th next iteration; The last iteration writes into the
** first character, and returns the next pointer to the previous iteration,
** which only then execute its own logic.
**
** In a way, the very last iteration is executed first.
*/

static char	*ft_itoa_write(int nb, const char *base, int dozen, char *output)
{
	if (nb <= -dozen || dozen <= nb)
		output = ft_itoa_write(nb / dozen, base, dozen, output);
	else if (nb < 0)
		*(output++) = '-';
	nb %= dozen;
	if (nb < 0)
		nb *= -1;
	*output = base[nb];
	output++;
	*output = '\0';
	return (output);
}

char		*ft_itoa_base(int nbr, const char *base)
{
	size_t	len;
	int		dozen;
	long	digit;
	char	*result;

	if (!(dozen = base_size(base)))
		return (0);
	len = 1;
	digit = nbr;
	if (digit < 0)
	{
		digit *= -1;
		len++;
	}
	while (digit >= dozen)
	{
		len++;
		digit /= dozen;
	}
	if (!(result = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_itoa_write(nbr, base, dozen, result);
	return (result);
}
