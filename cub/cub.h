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

/*
** Represents the raw, unprocessed content of a cub file.
** @var t_v2i resolution	The defined resolution of the screen.
** @var char[] north	The path to the northern texture.
** @var char[] south	The path to the southern texture.
** @var char[] east 	The path to the eastern  texture.
** @var char[] west 	The path to the western  texture.
** @var char[] sprite	The path to the spritern texture. :o)
** @var union u_color floorcol	The colour of the floor.
** @var union u_color ceilcol	The colour of the ceiling.
** @var t_v2i mapsize	The maximum dimensions of the map.
** @var char[height-1-y][x] tiles	The individual tiles of the map.
** 	Each row of the array may still be SMALLER than the maximum width.
*/

typedef struct s_cubfile	t_cubfile;
struct	s_cubfile
{
	struct s_v2i	resolution;

	char			*north;
	char			*south;
	char			*east;
	char			*west;

	char			*sprite;

	union u_color	floorcol;
	union u_color	ceilcol;

	struct s_v2i	mapsize;
	char			**tiles;
};

/*
** @var t_v2i resolution	The effective resolution of the screen.
** @var t_mlx_img north	The northern texture.
** @var t_mlx_img south	The southern texture.
** @var t_mlx_img east 	The eastern  texture.
** @var t_mlx_img west 	The western  texture.
** @var t_mlx_img sprite	The sprite texture.
** @var union u_color floorcol	The colour of the floor.
** @var union u_color ceilcol	The colour of the ceiling.
** @var t_v2i mapsize	The dimensions of the map.
** @var char[x,y] tiles	The individual tiles of the map.
** 	Blanks are filled in with \0.
** 	The player is replaced with a '0'.
**
** @var t_v2i playerspawn	The original position of the player.
** @var	float playerspanangle	The angle in degree the player is originaly rot
** ated around the Z axis.
*/

typedef struct s_cubworld	t_cubworld;
struct	s_cubworld
{
	struct s_v2i	resolution;

	void			*northpath;
	void			*southpath;
	void			*eastpath;
	void			*westpath;
	void			*spritepath;

	union u_color	floorcol;
	union u_color	ceilcol;

	struct s_v2i	mapsize;
	char*const		*tiles;

	struct s_v2i	playerspawn;
	float			playerspawnangle;

	t_mlx_img		north;
	t_mlx_img		south;
	t_mlx_img		east;
	t_mlx_img		west;
	t_mlx_img		sprite;
};

union	u_cub
{
	struct s_cubworld	world;
	struct s_cubfile	file;
};

void	parsefile(t_cubfile *this, int fd);
void	cubfile2world(union u_cub *this);
char	tile(t_cubworld *this, int x, int y);

#endif
