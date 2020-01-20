/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 11:56:31 by abaur             #+#    #+#             */
/*   Updated: 2020/01/20 13:45:01 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGBUILDER_H
# define STRINGBUILDER_H

# include <stdlib.h>

typedef struct s_strb	t_strb;
struct	s_strb
{
	size_t	capacity;
	size_t	size;
	char	*content;
};

t_strb	*createstrbuilder(void);
short	strbappend(t_strb *builder, char c);
char	*strbflush(t_strb *builder);

#endif
