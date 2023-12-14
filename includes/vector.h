/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:56:07 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/11/23 17:35:43 by abeihaqi         ###   ########.fr       */
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

# include <stdbool.h>

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
	double	x;
	double	y;
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
	double	x;
	double	y;
	double	z;
}	t_vector;

/**
 * @struct t_vector4
 * @brief Represents a 4D vector.
 *
 * This struct encapsulates the components of a 4D vector, including x, y, z,
 * and w.
 *
 * @var t_vector4::x
 * The x component of the vector.
 *
 * @var t_vector4::y
 * The y component of the vector.
 *
 * @var t_vector4::z
 * The z component of the vector.
 *
 * @var t_vector4::w
 * The w component of the vector.
 *
 * Use this struct to represent and manipulate 4D vectors in mathematical
 * operations.
 */
typedef struct s_vector4
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_vector4;

/**
 * @typedef t_vector
 * @brief Alias for a vector structure representing color.
 *
 * This typedef defines an alias where t_color is equivalent to t_vector,
 * treating a vector structure as a color.
 */
typedef t_vector	t_color;

/**
 * @struct t_quadratic
 * @brief Represents coefficients and solutions of a quadratic equation.
 *
 * This struct encapsulates the coefficients (a, b, c), the discriminant
 * (delta), solutions (t[2]), hit flags (hit[2]), distances (dist[2]), and a
 * constant factor (k) for a quadratic equation.
 *
 * @var t_quadratic::a
 * Coefficient 'a' in the quadratic equation.
 *
 * @var t_quadratic::b
 * Coefficient 'b' in the quadratic equation.
 *
 * @var t_quadratic::c
 * Coefficient 'c' in the quadratic equation.
 *
 * @var t_quadratic::delta
 * Discriminant of the quadratic equation.
 *
 * @var t_quadratic::t
 * Solutions to the quadratic equation.
 *
 * @var t_quadratic::hit
 * Flags indicating if the corresponding solution hit an object.
 *
 * @var t_quadratic::dist
 * Distances to the intersection points corresponding to the solutions.
 *
 * @var t_quadratic::k
 * Constant factor for the quadratic equation.
 *
 * Use this struct to represent and solve quadratic equations in ray tracing.
 */
typedef struct s_quadratic
{
	double		a;
	double		b;
	double		c;
	double		delta;
	double		t[2];
	bool		hit[2];
	double		dist[2];
	double		k;
}	t_quadratic;

/**
 * Calculate the dot product of two vectors.
 *
 * This function calculates and returns the dot product of two input vectors.
 *
 * @param vector1 The first input vector.
 * @param vector2 The second input vector.
 * @return The dot product of the two input vectors.
 */
double		dot(t_vector vector1, t_vector vector2);

/**
 * Calculate the cross product of two vectors.
 *
 * This function calculates and returns the cross product of two input vectors.
 *
 * @param vector1 The first input vector.
 * @param vector2 The second input vector.
 * @return The cross product vector resulting from the inputs.
 */
t_vector	cross(t_vector vector1, t_vector vector2);

/**
 * Normalize a vector to unit length.
 *
 * This function normalizes an input vector, converting it to a unit vector with
 * the same direction but a length of 1.
 *
 * @param vector The input vector to be normalized.
 * @return The normalized unit vector.
 */
t_vector	norm(t_vector vector);

/**
 * Perform vector addition between two vectors.
 *
 * This function adds two input vectors and returns the resulting vector.
 *
 * @param vector1 The first input vector.
 * @param vector2 The second input vector.
 * @return The vector sum of the two input vectors.
 */
t_vector	v_add(t_vector vector1, t_vector vector2);

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
t_vector	v_sub(t_vector vector1, t_vector vector2);

/**
 * @brief Divide a vector by a scalar.
 *
 * This function divides each component of the input vector by the given scalar,
 * and returns the resulting vector.
 *
 * @param vector The input vector.
 * @param scalar The scalar value to divide by.
 * @return The resulting vector after division.
 */
t_vector	v_div(t_vector vector, double scalar);

/**
 * @brief Calculate the magnitude (length) of a vector.
 *
 * This function calculates and returns the magnitude (length) of the input
 * vector.
 *
 * @param vector The input vector.
 * @return The magnitude of the input vector.
 */
double		magnitude(t_vector vector);

/**
 * @brief Scale a vector by a scalar.
 *
 * @param v      The vector to be scaled.
 * @param scalar The scalar value to scale the vector by.
 * @return       The resulting scaled vector.
 */
t_vector	v_scale(t_vector v, double scalar);

#endif