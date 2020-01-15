/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:19:44 by abaur             #+#    #+#             */
/*   Updated: 2020/01/13 15:36:30 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*
** Allocates a string capable of holding the entirety of the chained buffers,
** plus a Null terminator.
** @param t_gnlbuffer* first The first link of the buffer chain
** @return The allocated string, or NULL if the allocation fails.
*/

static char	*bufmalloc(t_gnlbuffer *first)
{
	t_gnlbuffer	*last;
	size_t		len;
	size_t		i;

	i = 0;
	last = first;
	while (last->next)
	{
		last = last->next;
		i++;
	}
	len = i * BUFFER_SIZE;
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	len += i;
	return (malloc(len + 1));
}

/*
** Merge all chained buffers into a single string, and frees the buffer.
** If the destination is NULL, the buffers are freed anyway.
** @param t_gnlbuffer* first The first link of the buffer chain. May be NULL.
** @param char** dt	The destination string.
** If non-NULL, the destination is assumed large enough to fit the buffer in.
** @return dst
*/

static char	*flushbuff(t_gnlbuffer *first, char *dst)
{
	t_gnlbuffer *current;
	t_gnlbuffer *prev;
	char		*cursor;
	size_t		i;

	i = 0;
	cursor = dst;
	current = first;
	while (current && current->content[i])
	{
		if (dst)
			*(cursor++) = current->content[i++];
		if (!dst || i == BUFFER_SIZE)
		{
			i = 0;
			prev = current;
			current = current->next;
			free(prev);
		}
	}
	if (dst)
		*cursor = '\0';
	return (dst);
}

/*
** Buffers the given file, and fetches the next character on each call.
** @param int fd The file descriptor to read.
** @param char* dst The adress where to write the character.
** @return
**  1 if a character is read
**  0 upon reading EOF, EOF is output to dst.
** -1 in case of error
*/

int			get_next_char(int fd, char *dst)
{
	static char	buffer[BUFFER_SIZE] = { 0 };
	static int	offset = BUFFER_SIZE;
	static int	readsize = BUFFER_SIZE;

	if (offset >= readsize)
	{
		offset = 0;
		readsize = read(fd, buffer, BUFFER_SIZE);
		if (readsize == 0)
			*dst = EOF;
		if (readsize < 1)
			return (readsize);
	}
	*dst = buffer[offset++];
	return (1);
}

/*
** Appends the given character to the chained buffer.
** Allocates and binds more links as needed.
** @param t_gnlbuffer** current Outputs the pointer to the current buffer.
** May be passed NULL for initialization.
** @param char value The character value to append;
** @return
** 	 0 OK
** 	-1 Allocation failed.
*/

static int	bufappend(t_gnlbuffer **current, char value)
{
	t_gnlbuffer *next;

	if (*current == NULL || (*current)->size == BUFFER_SIZE)
	{
		next = malloc(sizeof(t_gnlbuffer));
		if (next == NULL)
			return (-1);
		next->next = NULL;
		next->size = 0;
		if (*current)
			(*current)->next = next;
		*current = next;
	}
	(*current)->content[(*current)->size] = value;
	(*current)->size++;
	return (0);
}

int			get_next_line(int fd, char **line)
{
	t_gnlbuffer *chainedbuffer;
	t_gnlbuffer *current;
	char		value;
	int			err;

	chainedbuffer = NULL;
	current = NULL;
	while (0 <= (err = get_next_char(fd, &value)))
	{
		if (value == '\n' || value == (char)EOF)
			value = '\0';
		if (bufappend(&current, value) < 0)
			return (-1 | (int)flushbuff(chainedbuffer, NULL));
		if (!chainedbuffer)
			chainedbuffer = current;
		if (value == '\0')
			break ;
	}
	if (err < 0)
		*line = flushbuff(chainedbuffer, NULL);
	else
		*line = flushbuff(chainedbuffer, bufmalloc(chainedbuffer));
	return (*line ? err : -1);
}
