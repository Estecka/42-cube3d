/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:14:36 by abaur             #+#    #+#             */
/*   Updated: 2020/01/22 11:29:46 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THROW_H
# define THROW_H

# include <stdarg.h>

void	throw(int status, char *errformat, ...
) __attribute__((format(printf,2,3)));

void	throwif(short condition, int status, char *errformat, ...
) __attribute__((format(printf,3,4)));

void	vthrow(int status, char *errformat, va_list args);

#endif
