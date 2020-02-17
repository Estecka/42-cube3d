/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_util.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:55:08 by abaur             #+#    #+#             */
/*   Updated: 2020/01/28 16:48:23 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_UTIL_H
# define CUB_UTIL_H

# define R	82
# define NO	20302
# define SO 20307
# define WE 17751
# define EA	16709
# define S	83
# define F	70
# define C	67
# define MP	825307441

# include "cub.h"
# include "../dynarray/dynarray.h"

void	parsefield(char *line, t_cubfile *dst);
void	parseresolution(const char *line, int *width, int *height);
char	*parsetexpath(const char *line);
t_rgba	parsecolor(const char *line);
void	parsegridrow(t_cubfile *this, char *line, t_dynarray *array);
void	escaperoom(t_cubworld *this, char*const *checklist);

#endif
