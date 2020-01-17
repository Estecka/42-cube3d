/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:23:51 by abaur             #+#    #+#             */
/*   Updated: 2019/12/03 11:31:49 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

# include "bufferutil.h"

int			ft_vprintf(const char *format, va_list args);
int			ft_printf(const char *format, ...);

/*
** Internals
*/

typedef unsigned int	t_uint;
typedef unsigned long	t_ulong;

typedef struct s_pftag	t_pftag;
typedef int	(*t_writer)(t_pftag*);

struct		s_pftag
{
	const char		*src;
	t_buffer		*buffer;
	int				(*printer)(t_buffer*, char);

	char			type;
	t_writer		writer;

	long			argument;
	int				padsize;
	int				precision;

	unsigned short	sharped: 1;
	unsigned short	minused: 1;
	unsigned short	plused : 1;
	unsigned short	spaced : 1;
	unsigned short	zeroed : 1;
};

void		parsetag(const char **format, t_pftag *tag, va_list args);

int			w_intbase(t_pftag *tag, const char *base, short uint);

int			w_string(t_pftag *tag);
int			w_character(t_pftag *tag);
int			w_deci(t_pftag *tag);
int			w_udeci(t_pftag *tag);
int			w_hexa(t_pftag *tag);
int			w_hexaup(t_pftag *tag);
int			w_octa(t_pftag *tag);
int			w_pointer(t_pftag *tag);
#endif
