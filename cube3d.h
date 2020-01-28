/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/01/28 16:42:35 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <errno.h>
# include "throw.h"
# include "libft/libft.h"

typedef unsigned int	t_uint;
typedef unsigned long	t_ulong;

typedef struct s_rgb	t_rgb;
struct	s_rgb
{
	unsigned int	b : 8;
	unsigned int	g : 8;
	unsigned int	r : 8;
};

typedef struct s_rgba	t_rgba;
struct	s_rgba
{
	unsigned int	b : 8;
	unsigned int	g : 8;
	unsigned int	r : 8;
	unsigned int	a : 8;
};

typedef union u_color	t_color;
union	u_color
{
	unsigned int	raw;
	struct s_rgb	rgb;
	struct s_rgba	rgba;
};

typedef struct s_vec2i	t_vec2i;
struct	s_vec2i
{
	int	x;
	int	y;
};

typedef struct s_vec3	t_vec3;
struct	s_vec3
{
	float	x;
	float	y;
	float	z;
};

typedef struct s_vec4	t_vec4;
struct	s_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;
};

void	*g_mlx;
void	*g_window;

#endif
