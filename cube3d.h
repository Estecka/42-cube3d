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
# include "mlxpp/mlxpp.h"
# include "throw.h"
# include "libft/libft.h"

typedef unsigned int	t_uint;
typedef unsigned long	t_ulong;

typedef struct s_v2i	t_v2i;
struct	s_v2i
{
	signed int	x;
	signed int	y;
};

void	*g_mlx;
short	g_log;

#endif
