/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:12:41 by abaur             #+#    #+#             */
/*   Updated: 2020/01/27 15:17:37 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODE_H
# define KEYCODE_H


# ifdef __APPLE__
#  define KCESC	53

#  define KCW	13
#  define KCA	 0
#  define KCS	 1
#  define KCD	 2

#  define KCLEFT	123
#  define KCRIGHT	124
#  define KCDOWN	125
#  define KCUP		126

#  define KCLSHIFT	257
#  define KCSPACE	49

# elif __linux__

#  define KCESC	65307

#  define KCZ   122
#  define KCQ   113
#  define KCW	119
#  define KCA	 97
#  define KCS	115
#  define KCD	100

#  define KCLEFT	65361
#  define KCRIGHT	65363
#  define KCDOWN	65364
#  define KCUP		65362

#  define KCLSHIFT	65505
#  define KCSPACE	32
# endif

#endif
