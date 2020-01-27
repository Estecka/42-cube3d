/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:01:12 by abaur             #+#    #+#             */
/*   Updated: 2020/01/27 12:20:37 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stringbuilder.h"

#include <errno.h>
#include "../throw.h"

/*
** Allocates and initialize a stringbuilder.
** @return t_strb The stringbuilder, or NULL if allocation failed.
*/

t_strb	*createstrbuilder(void)
{
	t_strb	*builder;

	if (!(builder = malloc(sizeof(struct s_strb))))
		throw(errno, "[FATAL] StringBuilder malloc failed. %d", errno);
	builder->content = malloc(sizeof(char) * 32);
	if (!builder->content)
	{
		free(builder);
		throw(errno, "[FATAL] StringBuilder malloc failed. %d", errno);
	}
	builder->capacity = 32;
	builder->size = 1;
	builder->content[0] = '\0';
	return (builder);
}

/*
** Appends the given character to the string.
** The resulting string is always NULL terminated.
** The capacity of the builder is doubled whenever it becomes too small.
** The original string is preserved if allocation fails.
** @param t_strb* builder The stringbuilder to use.
** @param char c The character to append.
** @return short
** 	 0 OK
** 	-1 Allocation failed
*/

short	strbappend(t_strb *builder, char c)
{
	char	*newstr;
	size_t	i;

	if (builder->size >= builder->capacity)
	{
		if (!(newstr = malloc(builder->capacity * 2)))
			throw(errno, "[FATAL] StringBuilder append failed. %d", errno);
		i = 0;
		while (i < builder->capacity)
		{
			newstr[i] = builder->content[i];
			i++;
		}
		free(builder->content);
		builder->content = newstr;
		builder->capacity *= 2;
	}
	builder->content[builder->size - 1] = c;
	builder->content[builder->size] = '\0';
	builder->size++;
	return (0);
}

/*
** Frees the given stringbuilder, and return the built string.
** @param t_strb* builder The string builder to free.
** @return char* The built string.
*/

char	*strbflush(t_strb *builder)
{
	char *result;

	result = builder->content;
	free(builder);
	return (result);
}
