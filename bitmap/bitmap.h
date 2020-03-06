/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 12:54:24 by abaur             #+#    #+#             */
/*   Updated: 2020/03/05 12:55:18 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMAP_H
# define BITMAP_H

# include "../mlxpp/mlxpp.h"

/*
** Initialize a mxl image from a bmp file.
** If the method fails, the mlx image will be cleared.
** @return bool
** 	true 	OK
** 	false	Invalid file, or Allocation failed.
*/
short	bmp_read(t_mlx_img *this, int fd);

short	bmp_write(t_mlx_img *this, int fd);

#endif
