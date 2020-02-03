/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:36:29 by abaur             #+#    #+#             */
/*   Updated: 2020/02/03 15:13:10 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "../cube3d.h"
# include "../ft_math/ft_math.h"

extern void	*g_mlx;
extern void	*g_window;

void		renderinit(unsigned int width, unsigned int height);
int			renderflush(void *mlx);

void		renderset(unsigned int x, unsigned int y, union u_color color);
void		renderquad(t_quad quad);
#endif
