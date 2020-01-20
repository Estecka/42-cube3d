/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tag_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:33:49 by abaur             #+#    #+#             */
/*   Updated: 2020/01/20 16:11:59 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "bufferutil.h"

#include <unistd.h>
#include <stdarg.h>

/*
** Returns the appropriate method to write the given tag type.
**
** The returned method's prototype will be `int (t_pftag*, va_list)`
** It moves the va_list forward as required by the tag,
** and returns the amount of characters printed.
** NULL is returned if the tag type is not supported.
*/

static t_writer	pickwriter(char c)
{
	if (c == 's')
		return (w_string);
	if (c == 'c')
		return (w_character);
	if (c == 'd' || c == 'i')
		return (w_deci);
	if (c == 'u')
		return (w_udeci);
	if (c == 'o')
		return (w_octa);
	if (c == 'x')
		return (w_hexa);
	if (c == 'X')
		return (w_hexaup);
	if (c == 'p')
		return (w_pointer);
	else
		return (NULL);
}

/*
** Parses a positive number and returns it.
** Leaves the cursor onto the last character parsed,
** or moves it backward if no digits was parsed.
** If the string is '*', an argument from the va_list is returned instead.
*/

static int		parsenbr(const char **src, va_list args)
{
	int	result;

	result = 0;
	if (**src == '*')
		return (int)va_arg(args, long);
	while (ft_isdigit(**src))
	{
		result *= 10;
		result += **src - '0';
		(*src)++;
	}
	(*src)--;
	return (result);
}

/*
** Parses the `#-+ 0' section of the tag.
** Alters the given tag and moves the cursor forward accordingly.
*/

static void		parseflags(t_pftag *tag, const char **src, va_list args)
{
	while (**src)
	{
		if (**src == '#')
			tag->sharped = 1;
		else if (**src == '-')
			tag->minused = 1;
		else if (**src == '+')
			tag->plused = 1;
		else if (**src == ' ')
			tag->spaced = 1;
		else if (**src == '0')
			tag->zeroed = 1;
		else if (**src == '*' || ft_isdigit(**src))
			tag->padsize = parsenbr(src, args);
		else if (**src == '.')
		{
			(*src)++;
			tag->precision = parsenbr(src, args);
		}
		else
			return (void)(tag->type = **src ? *((*src)++) : **src);
		(*src)++;
	}
}

/*
** Builds a pftag object after the given string.
** Disable incompatible tags when applicable.
** Moves the arguments forward as needed.
** Moves `src` forward until the first caracter after the tag.
** If the tag is invalid, `src` is only moved by one.
*/

void			parsetag(const char **src, t_pftag *tag, va_list args)
{
	ft_bzero(tag, sizeof(t_pftag));
	tag->src = *src;
	tag->precision = -1;
	parseflags(tag, src, args);
	if (tag->padsize < 0)
	{
		tag->padsize *= -1;
		tag->minused = 1;
	}
	if (tag->plused)
		tag->spaced = 0;
	if (tag->minused)
		tag->zeroed = 0;
	tag->buffer = newbuffer(tag->padsize, tag->zeroed ? '0' : ' ');
	tag->writer = pickwriter(tag->type);
	tag->printer = tag->minused ? buffaddl : buffaddr;
	if (!tag->writer)
	{
		tag->writer = w_character;
		tag->argument = tag->type;
		tag->type = 0;
	}
	else
		tag->argument = va_arg(args, long);
}
