/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxpp.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 11:23:57 by abaur             #+#    #+#             */
/*   Updated: 2020/03/05 11:24:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXPP_H
# define MLXPP_H

/*
** A pointer to the running instance of MinilibX
** It is up to you to set this value appropriately.
*/
extern void	*g_mlx;

typedef struct s_rgb24	t_rgb;
typedef struct s_rgb24	t_rgb24;
struct		s_rgb24
{
	unsigned int	b : 8;
	unsigned int	g : 8;
	unsigned int	r : 8;
};

typedef struct s_rgba32	t_rgba;
typedef struct s_rgba32	t_rgba32;
struct		s_rgba32
{
	unsigned int	b : 8;
	unsigned int	g : 8;
	unsigned int	r : 8;
	unsigned int	a : 8;
};

typedef union u_color	t_color;
typedef union u_color	t_color32;
union		u_color
{
	unsigned int	raw;
	char			bytes[4];
	struct s_rgb24	rgb;
	struct s_rgba32	rgba;
};

/*
** @var void* ptr	A pointer to the actual picture object.
** 	This is the pointer that needs to bee passed around the vanilla minilibx me
** thods. It should be freed when appropriate.
** @union u_color	A pointer to he array of pixels.
**	The `union u_color` type is only appropriate with images encoded in 32-bits
**  argb.
** 	This pointer is a part of `*ptr` and cannot be freed.
** @var unsigned int width, height	The intended resolution of the picture.
** @var bits_per_pixel	The color depth of the texels.
** 	Assumed to be 32bits in this module.
** @var int	size_line	The size of a single scanline in bits.
** @var int	pixel_line	The size of a single scanline in pixels
** 	This may actually be greater than `width`.
** @var int	endian	The picture's endian.
** 	Assumed to be little in this module.
*/
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

/*
** Sets a texel in a mlx_img.
** The color format is assumed to be 32-bits ARGB.
** @param t_mlx_img* this	The texture to write.
** @param unsigned int x, y	The coordinates of the texel.
** @param t_color	The color value.
*/
void		mlx_img_set(t_mlx_img *this, unsigned int x, unsigned int y,
	t_color col);

/*
** Gets a texel's color.
** The color format is assumed to be 32-bits ARGB.
** @param t_mlx_img* this	The texture to read.
** @param unsigned int x, y	The coordinates of the texel.
*/
t_color		mlx_img_get(t_mlx_img *this, unsigned int x, unsigned int y);
/*
** Gets a pointer to a texel.
** The color format is assumed to be 32-bits ARGB.
** @param t_mlx_img* this	The texture to read.
** @param unsigned int x, y	The coordinates of the texel.
*/
t_color		*mlx_img_getptr(t_mlx_img *this, unsigned int x, unsigned int y);

/*
** Gets a color on a texture from normalized coordinates.
** @param t_mlx_img* this	The texture to read.
** @param float u, v	The coordinates to sample, in the [0;1] range.
** 	Out of bounds  coordinates are clamped.
*/
t_color		mlx_img_sample(t_mlx_img *this, float u, float v);

/*
** Allocates a vanilla mlx picture, and fills its informations into the given o
** bject.
** This requires `g_mlx` to be set.
** @param t_mlx_img* this	The object to initialize.
** @param unsigned int width, height	The intended resolution of the picture.
** @return bool
** 	true 	OK
** 	false	Allocation failed.
*/
short		mlx_img_init(t_mlx_img *this,
	unsigned int width, unsigned int height);

#endif
