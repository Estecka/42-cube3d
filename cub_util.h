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
# include "stringbuilder/stringbuilder.h"

void	parseresolution(const char *line, int *width, int *height);
char	*parsetexpath(const char *line);
t_rgba	parsecolor(const char *line);
t_strb	*parsegridwidth(const char *line, t_mapfile *file);
short	validategridrow(const char *line, t_mapfile *file);
int		parsegridrow(const char *line, t_mapfile *file, t_strb *builder);

#endif
