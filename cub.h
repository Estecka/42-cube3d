/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/01/20 14:19:53 by abaur            ###   ########.fr       */
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
	int				screenwdt;
	int				screenhgt;

	char			*north;
	char			*south;
	char			*east;
	char			*west;

	char			*sprite;

	t_color			floorcol;
	t_color			ceilcol;

	unsigned int	mapwdt;
	unsigned int	maphgt;
	char*const		*map;
};

void	parsemap(int fd, t_mapfile *dst);

#endif
