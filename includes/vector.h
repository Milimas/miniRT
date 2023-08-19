/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:56:07 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/19 22:21:30 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "minirt.h"

/*
 * Structure representing a 3D vector.
 *
 * This struct encapsulates the components of a 3D vector, representing points
 * or directions in 3D space.
 *
 * Members:
 * - x: The x-component of the vector.
 * - y: The y-component of the vector.
 * - z: The z-component of the vector.
 * - w: The w-component of the vector.
 *
 * Use this struct to define and manage 3D vectors within your code.
 */
typedef struct s_vector
{
	int	x;
	int	y;
	int	z;
	int	w;
}	t_vector;

#endif