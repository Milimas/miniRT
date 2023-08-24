/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:56:07 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/24 22:35:34 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file vector.h
 * @brief Header file for vector-related functions and structures.
 *
 * This file contains declarations for functions and structures related to
 * handling and manipulating vectors in a 3D space.
 */

#ifndef VECTOR_H
# define VECTOR_H

# include "minirt.h"

/**
 * @struct t_pixel
 * @brief Represents the position of a pixel within an image or screen.
 *
 * This structure encapsulates the x and y coordinates of a pixel's position.
 *
 * @var t_pixel::x
 * The x-coordinate of the pixel.
 *
 * @var t_pixel::y
 * The y-coordinate of the pixel.
 *
 * Use this structure to manage pixel positions within an image or screen.
 */
typedef struct s_pixel
{
	int	x;
	int	y;
}	t_pixel;

/**
 * @struct s_vector
 * @brief Represents a 3D vector with x, y, and z components.
 *
 * This struct encapsulates the x, y, and z components of a 3D vector.
 *
 * @var s_vector::x
 * The x-component of the vector.
 *
 * @var s_vector::y
 * The y-component of the vector.
 *
 * @var s_vector::z
 * The z-component of the vector.
 *
 * Use this struct to handle 3D vector calculations and manipulations.
 */
typedef struct s_vector
{
	int	x;
	int	y;
	int	z;
}	t_vector;

/**
 * Calculate the dot product of two vectors.
 *
 * This function calculates and returns the dot product of two input vectors.
 *
 * @param vector1 The first input vector.
 * @param vector2 The second input vector.
 * @return The dot product of the two input vectors.
 */
float		dot_product(t_vector vector1, t_vector vector2);

/**
 * Calculate the cross product of two vectors.
 *
 * This function calculates and returns the cross product of two input vectors.
 *
 * @param vector1 The first input vector.
 * @param vector2 The second input vector.
 * @return The cross product vector resulting from the inputs.
 */
t_vector	cross_product(t_vector vector1, t_vector vector2);

/**
 * Normalize a vector to unit length.
 *
 * This function normalizes an input vector, converting it to a unit vector with
 * the same direction but a length of 1.
 *
 * @param vector The input vector to be normalized.
 * @return The normalized unit vector.
 */
t_vector	normalize_vector(t_vector vector);

/**
 * Perform vector addition between two vectors.
 *
 * This function adds two input vectors and returns the resulting vector.
 *
 * @param vector1 The first input vector.
 * @param vector2 The second input vector.
 * @return The vector sum of the two input vectors.
 */

t_vector	vector_addition(t_vector vector1, t_vector vector2);

/**
 * Perform vector subtraction between two vectors.
 *
 * This function subtracts the second input vector from the first input vector
 * and returns the resulting vector.
 *
 * @param vector1 The first input vector.
 * @param vector2 The second input vector.
 * @return The vector difference between the two input vectors.
 */
t_vector	vector_subtraction(t_vector vector1, t_vector vector2);

#endif