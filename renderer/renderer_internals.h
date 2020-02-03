/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_internals.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:18:28 by abaur             #+#    #+#             */
/*   Updated: 2020/02/03 17:02:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_INTERNALS_H
# define RENDERER_INTERNALS_H

# include "renderer.h"
# include "../ft_math/ft_math.h"
# include "../minilibx/mlx.h"

typedef struct s_mlx_img	t_mlx_img;
struct			s_mlx_img
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

typedef struct s_float_img	t_float_img;
struct			s_float_img
{
	unsigned int	width;
	unsigned int	height;
	float			*content;
};

t_float_img		g_zbuffer;
t_mlx_img		g_rendertex;
const t_bbox	g_clipspace;

void			mlx_img_set(t_mlx_img *this, unsigned int x, unsigned int y,
	union u_color col);

short			zbuffinit(unsigned int width, unsigned int height);
void			zbuffclear();
float			zbuffget(unsigned int x, unsigned int y);
void			zbuffset(float value, unsigned int x, unsigned int y);
short			zbuffcmp(float value, unsigned int x, unsigned int y);

#endif
