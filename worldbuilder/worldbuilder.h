/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worldbuilder.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:39:45 by abaur             #+#    #+#             */
/*   Updated: 2020/02/17 14:39:47 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLDBUILDER_H
# define WORLDBUILDER_H

# include "../ft_math/ft_math.h"
# include "../cub/cub.h"
# include "../renderer/renderer.h"

/*
** Struct to be sent to the renderer module.
** The reference is to be worked on by the renderer.
** @var t_quad vertices	The vertices of the mesh in view space.
** @var t_mlx_img* texture The texture to apply.
*/

typedef struct s_rendermesh	t_mesh;
struct	s_rendermesh
{
	t_seg2		vertices;
	t_mlx_img	*texture;
};

/*
** A mesh that is'nt supposed to move at all.
** Its world coordinates are pre-baked, from g_wallmesh.
** @var t_quad vertices	The vertices of the mesh in world space.
** @var t_rendermesh renderinfo
*/

typedef struct s_staticmesh	t_staticmesh;
struct	s_staticmesh
{
	t_seg2				vertices;
	struct s_rendermesh renderinfo;
};

typedef struct s_transform		t_transform;
struct	s_transform
{
	t_v2	position;
	float	rotation;
	t_mx3	l2wmx;
	t_mx3	w2lmx;
};

typedef struct s_worldmesh		t_worldmesh;
struct	s_worldmesh
{
	unsigned int	wallcount;
	t_staticmesh	*walls;
	unsigned int	spritecount;
	t_v2			*sprites;
	t_mlx_img		*spritetexture;
};

t_transform		g_player;

void	worldinit(t_cubworld *world);
void	renderworld();

void	retransform(t_transform *this);

#endif
