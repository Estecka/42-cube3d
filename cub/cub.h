/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/01/28 16:12:34 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../cube3d.h"

typedef struct s_cubfile	t_cubfile;
struct	s_cubfile
{
	int				screenwdt;
	int				screenhgt;

	char			*north;
	char			*south;
	char			*east;
	char			*west;

	char			*sprite;

	union u_color	floorcol;
	union u_color	ceilcol;

	unsigned int	mapwdt;
	unsigned int	maphgt;
	char			**tiles;
};

void	parsefile(t_cubfile *this, int fd);

#endif
