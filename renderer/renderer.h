/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:36:29 by abaur             #+#    #+#             */
/*   Updated: 2020/02/05 11:42:25 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "../cube3d.h"
# include "../ft_math/ft_math.h"

typedef struct s_mlx_img	t_mlx_img;
struct		s_mlx_img
{
	void			*ptr;
	union u_color	*pixels;
	unsigned int	width;
	unsigned int	height;
	int				bits_per_pixel;
	int				size_line;
	int				pixel_line;
	int				endian;
};

extern void		*g_mlx;
extern void		*g_window;

/*
** @var float altitude	The height of the camera. 0.5f by default.
** @var float altitude	The vertical viewing angle. 0.5f by default.
*/

extern float	g_altitude;
extern float	g_angle;

void			renderinit(unsigned int width, unsigned int height);
void			renderflush();

void			renderclear(union u_color color);
void			rendersky(union u_color floor, union u_color s);
void			renderset(unsigned int x, unsigned int y, union u_color color);

void			renderqueuestage(const t_seg2 segment);
void			renderbboard(const t_v2	*position);
void			renderqueueflush();
void			extrude();

#endif
