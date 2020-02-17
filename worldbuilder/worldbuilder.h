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
	t_quad		vertices;
	t_mlx_img	*texture;
};

/*
** A mesh that is'nt supposed to move at all.
** Its world coordinates are pre-baked, from g_wallmesh.
** @var t_quad vertices	The vertices of the mesh in world space.
** @var t_rendermesh renderinfo
*/

typedef struct s_staticmesh	t_staticmesh;
struct s_staticmesh
{
	t_quad				vertices;
	struct s_rendermesh renderinfo;
};

/*
** A mesh whose position is fixed, but orientation varies with the camera.
** The base mesh is assumedto be g_spritemesh.
** @var t_quad vertices	The position of the mesh in world space.
** @var t_rendermesh renderinfo
*/

typedef struct s_billboardmesh	t_billboardmesh;
struct s_billboardmesh
{
	struct s_v3			position;
	struct s_rendermesh renderinfo;
};

void	worldinit(t_cubworld *world);
void	renderworld(t_v3 position, t_v4 rotation);

#endif
