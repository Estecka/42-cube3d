/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:17:50 by abaur             #+#    #+#             */
/*   Updated: 2019/11/18 11:40:11 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates and returns an array of strings,
** obtained by splitting the given string,
** using the given character as a separator.
**
** The array is NULL terminated.
*/

char	**ft_split(char const *s, char c)
{
	char				**results;
	unsigned int		wordcount;
	int					i;
	int					start;

	wordcount = 1;
	i = -1;
	while (s && s[++i])
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			wordcount++;
	if (!(results = (char**)malloc(sizeof(char*) * wordcount)))
		return (NULL);
	i = -1;
	start = 0;
	wordcount = 0;
	while (s && s[++i])
		if (s[i] != c)
		{
			if (i == 0 || s[i - 1] == c)
				start = i;
			if (s[i + 1] == c || s[i + 1] == '\0')
				results[wordcount++] = ft_substr(s, start, i + 1 - start);
		}
	results[wordcount] = NULL;
	return (results);
}

/*
** Applies the function `f` to each character of the given string
** to create a new string resulting fromsuccessive applications
** of f.
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*result;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len])
		len++;
	result = (char*)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (--len >= 0)
		result[len] = f ? f(len, s[len]) : 0;
	return (result);
}

/*
** Computes the lenght of `s` until the Nul terminator (excluded).
*/

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*(s++))
		len++;
	return (len);
}

/*
** Copies up to `dstsize` bytes from `src` to `dst`.
** Null terminator is garanteed and included in `dstsize`;
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!src || !dst)
		return (0);
	i = 0;
	while (1)
	{
		if (i == dstsize - 1)
			dst[i] = '\0';
		else if (i < dstsize)
			dst[i] = src[i];
		if (src[i] == '\0')
			return (i);
		i++;
	}
}

/*
** Appends `src` at the end of `dst`.
** `dst` will be up to `dstsize` bytes long, Null terminator included.
** The result is Null terminated, unless `dstsize` is smaller than `len(dst)`.
** Returns min(len(dst), dstsize) + len(src).
*/

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dst[i] && i < dstsize)
		i++;
	j = 0;
	while (1)
	{
		if (i == dstsize - 1)
			dst[i] = '\0';
		else if (i < dstsize)
			dst[i] = src[j];
		if (src[j] == '\0')
			return (i);
		i++;
		j++;
	}
}
