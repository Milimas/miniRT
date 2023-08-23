/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:56:07 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/23 20:03:30 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "minirt.h"

/*
 * Structure representing a pixel's position.
 *
 * This struct encapsulates the x and y coordinates of a pixel's position.
 *
 * Members:
 * - x: The x-coordinate of the pixel.
 * - y: The y-coordinate of the pixel.
 *
 * Use this struct to manage pixel positions within an image or screen.
 */
typedef struct s_pixel
{
	int	x;
	int	y;
}	t_pixel;

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
 *
 * Use this struct to define and manage 3D vectors within your code.
 */
typedef struct s_vector
{
	int	x;
	int	y;
	int	z;
}	t_vector;

#endif