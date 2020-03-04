/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_internals.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:18:28 by abaur             #+#    #+#             */
/*   Updated: 2020/02/06 10:41:42 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_INTERNALS_H
# define RENDERER_INTERNALS_H

# include "renderer.h"
# include "../ft_math/ft_math.h"
# include "../dynarray/dynarray.h"
# include "../minilibx/mlx.h"

typedef struct s_float_img	t_float_img;
struct			s_float_img
{
	unsigned int	width;
	unsigned int	height;
	float			*content;
};

/*
** A rendering environnement for a single quad.
** @var t_seg2 pixvert	The pixel coordinates of the vertices.
** @var t_m2a umx	A 2x1 matrix that transforms from figure space to UV space.
** @var t_m2a figspace	A 2x1 matrix that transforms a pixel from screen space
**  to figure space.
** @var	linefloat	The scalar of the segment's line equation.
** @var	lineoffset	The offset of the segment's line equation.
*/

typedef struct s_renderenv	t_renderenv;
struct			s_renderenv
{
	t_seg2	pixvert;
	t_mx2a	umx;
	t_mx2a	figspace;
	float	linescalar;
	float	lineoffset;
};

/*
** A endering environnement for a single column of the extruder.
** @var float u	The U coordinate on the texture.
** @var t_mx2a vmx	The matrix that converts a Y pixel coordinate to the corres
** ponding V coordinate on the texture.
** @var float depth	The depth of te pixel in clip space.
*/

typedef struct s_rendercol	t_rendercol;
struct			s_rendercol
{
	float	depth;
	float	u;
	t_mx2a	vmx;
	float	ymin;
	float	ymax;
};

/*
** @var t_bbox2 g_frustrum	The dimensions of the frustrum.
** @var t_mx3 g_projmx	A matrix that transform the frustrum cube into clip space.
** @var const t_bbox2	g_clipspace	The dimensions of the clip space.
*/

t_bbox2			g_frustrum;
t_mx3			g_projmx;
const t_bbox2	g_clipspace;

t_mlx_img		g_rendertex[2];
t_bbox2			g_screenbb;
unsigned int	g_screenwdt;
unsigned int	g_screenhgt;
float			g_aspect;

t_dynarray		g_renderqueue;

void			mlx_img_set(t_mlx_img *this, unsigned int x, unsigned int y,
	union u_color col);

void			getvmx(float this[2][1], float depth);

t_rendercol		*g_rendercols;
short			rcolinit(unsigned int width);
void			rcolclear();
float			rcolzget(unsigned int x);
void			rcolzset(unsigned int x, float value);
short			rcolzcmp(unsigned int x, float value);

t_float_img		g_zbuffer;
short			zbuffinit(unsigned int width, unsigned int height);
void			zbuffclear();
float			zbuffget(unsigned int x, unsigned int y);
void			zbuffset(unsigned int x, unsigned int y, float value);
short			zbuffcmp(unsigned int x, unsigned int y, float value);

void			renderqueueinit();

short			clipquad(const t_seg2 segment);
void			neartruncate(const t_seg2 segment, t_seg2 destination);
void			renderquad(const t_seg2 segment);
void			rasterize(t_renderenv *env);
void			extrude();

#endif
