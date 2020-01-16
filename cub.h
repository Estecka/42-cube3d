/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/01/16 12:49:17 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

typedef struct s_color		t_color;
typedef struct s_mapfile	t_mapfile;

struct	s_color
{
	unsigned int	r : 8;
	unsigned int	g : 8;
	unsigned int	b : 8;
	unsigned int	a : 8;
};

struct	s_mapfile
{
	int		width;
	int		height;

	char	*norh;
	char	*south;
	char	*east;
	char	*west;

	char	*sprite;

	t_color	floorcol;
	t_color	ceilcol;

	char	*map;
};

short	*parsemap(int fd, t_mapfile *dst);

#endif
