/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:39:45 by abaur             #+#    #+#             */
/*   Updated: 2020/02/17 14:39:47 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "worldbuilder.h"

/*
** Recomputes a transform's matrix and inverse matrix.
*/

void	retransform(t_transform *this)
{
	mx3init(this->l2wmx);
	mx3pos(this->l2wmx, &this->position);
	mx3angle(this->l2wmx, this->rotation);
	mx3invaff(this->l2wmx, this->w2lmx);
}
