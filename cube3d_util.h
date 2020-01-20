/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/01/20 15:17:15 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_UTIL_H
# define CUBE3D_UTIL_H

# include "libft/libft.h"
# include "errno.h"

typedef unsigned int	t_uint;
typedef unsigned long	t_ulong;

void	throw(int status, char *errformat, ...
) __attribute__((format(printf,2,3)));

#endif
