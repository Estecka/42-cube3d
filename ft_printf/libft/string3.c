/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 12:10:07 by abaur             #+#    #+#             */
/*   Updated: 2019/11/08 16:17:33 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
** Points to the first occurence of `c` in `s`
*/

char	*ft_strchr(const char *s, int c)
{
	while (1)
	{
		if (*s == c)
			return ((char*)s);
		if (!*s)
			return (NULL);
		s++;
	}
}

/*
** Locates the last occurence of `c` in `s` and points to it.
*/

char	*ft_strrchr(const char *s, int c)
{
	const char *result;

	result = NULL;
	while (1)
	{
		if (*s == (char)c)
			result = s;
		if (!*s)
			break ;
		s++;
	}
	return ((char*)result);
}

/*
** Locates the first occurence of `needle` in `haystack`,
** searching no further than `len` characters.
*/

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*result;
	size_t		i;
	size_t		j;

	if (!*needle)
		return ((char*)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		if (*needle == haystack[i])
		{
			j = 0;
			result = &haystack[i];
			while (j + i < len && needle[j] == haystack[j + i])
			{
				if (needle[j + 1] == '\0')
					return ((char*)result);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		diff;
	size_t	i;

	i = 0;
	diff = 0;
	while (!diff && i++ < n)
	{
		diff = (unsigned char)*s1 - (unsigned char)*s2;
		if (!*s1 || !*s2)
			break ;
		s1++;
		s2++;
	}
	return (diff);
}
