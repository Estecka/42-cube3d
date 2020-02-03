/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:36:29 by abaur             #+#    #+#             */
/*   Updated: 2020/02/03 12:55:47 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "./cube3d.h"
# include "../ft_math/ft_math.h"

void	*g_window;

void	*renderinit(unsigned int width, unsigned int height);

void	renderquad(t_quad quad);

void	renderclear(t_color);
void	rendercleardepth();

int		renderflush(void *mlx);h

#endif
