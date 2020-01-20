/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferutil.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:46:23 by abaur             #+#    #+#             */
/*   Updated: 2019/12/03 12:03:14 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFERUTIL_H
# define BUFFERUTIL_H

# include <stdlib.h>

typedef struct s_buffer	t_buffer;
struct		s_buffer
{
	size_t	capacity;
	void	(*flushmethod)(char c);

	char	*content;
	char	*lcursor;
	char	*rcursor;
};

t_buffer	*newbuffer(size_t capacity, char content);
int			flushbuffer(t_buffer *buffer);
int			buffaddl(t_buffer *buffer, char value);
int			buffaddr(t_buffer *buffer, char value);

#endif
