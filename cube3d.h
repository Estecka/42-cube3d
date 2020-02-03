/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/02/03 12:55:19 by abaur            ###   ########.fr       */
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

void	*g_mlx;

#endif
