/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:05:07 by abaur             #+#    #+#             */
/*   Updated: 2019/11/08 13:42:35 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	char	*c;
	size_t	i;

	c = s;
	i = 0;
	while (i < n)
		c[i++] = '\0';
}

/*
** Allocates enough memory for `count` objects that are `size` bytes long,
** and fills the memory with 0's.
*/

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	size *= count;
	result = malloc(size);
	if (result)
		ft_bzero(result, size);
	return (result);
}

/*
** Writes `len` bytes of value `c` to the string `b`.
*/

void	*ft_memset(void *b, int c, size_t len)
{
	char	*str;
	size_t	i;

	str = (char*)b;
	i = 0;
	while (i < len)
		str[i++] = (unsigned char)c;
	return (b);
}

/*
** Copies `n` bytes from memory area `src` to `dst`
*/

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((char*)dst)[i] = ((char*)src)[i];
		i++;
	}
	return (dst);
}

/*
** Copies bytes from string `src` to `dst`.
** If the character c occurs, the copy stops,
** and a pointer to the byte after the copy of c is returned;
** Otherwise, n bytes are copied, and NULL is returned.
*/

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*fro;
	unsigned char	*to;

	fro = (unsigned char*)src;
	to = (unsigned char*)dst;
	i = 0;
	while (i < n)
	{
		to[i] = fro[i];
		if (to[i] == (unsigned char)c)
			return (&(to[i + 1]));
		i++;
	}
	return (NULL);
}
