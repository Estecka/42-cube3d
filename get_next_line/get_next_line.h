/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:20:24 by abaur             #+#    #+#             */
/*   Updated: 2020/01/16 11:02:54 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# if BUFFER_SIZE > 0
#  define BUFFER 0
# else
#  define BUFFER
# endif

typedef struct s_gnlbuffer	t_gnlbuffer;
struct	s_gnlbuffer {
	t_gnlbuffer	*next;
	size_t		size;
	char		content[BUFFER_SIZE];
};

int		get_next_char(int fd, char *dst);
int		get_next_line(int fd, char **line);

#endif
