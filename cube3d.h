/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/01/22 11:38:05 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <errno.h>
# include "throw.h"
# include "libft/libft.h"

typedef unsigned int	t_uint;
typedef unsigned long	t_ulong;

typedef struct s_color	t_color;
struct	s_color
{
	unsigned int	r : 8;
	unsigned int	g : 8;
	unsigned int	b : 8;
	unsigned int	a : 8;
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

#endif
