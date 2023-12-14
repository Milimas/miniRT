/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:08:22 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/11/23 17:19:50 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"
# include <math.h>

/**
 * @union u_matrix
 * @brief Represents a 4x4 matrix or its components as vectors.
 *
 * This union allows representing a 4x4 matrix using a two-dimensional array
 * or its individual components as vectors.
 *
 * @var u_matrix::m
 * Two-dimensional array representing the elements of the matrix.
 *
 * @var u_matrix::r1
 * Vector representing the first row of the matrix.
 *
 * @var u_matrix::r2
 * Vector representing the second row of the matrix.
 *
 * @var u_matrix::r3
 * Vector representing the third row of the matrix.
 *
 * @var u_matrix::r4
 * Vector representing the fourth row of the matrix.
 *
 * Use this union to work with matrices in either array or vector form.
 */
typedef union u_matrix
{
	double	m[4][4];
	struct {
		t_vector	r1;
		t_vector	r2;
		t_vector	r3;
		t_vector	r4;
	};
}	t_matrix;

/**
 * @brief Create a 4x4 matrix representing a rotation around the X-axis.
 *
 * @param angle The rotation angle in radians.
 * @return A 4x4 matrix representing the rotation around the X-axis.
 */
t_matrix	matrix_rot_x(double angle);

/**
 * @brief Create a 4x4 matrix representing a rotation around the Y-axis.
 *
 * @param angle The rotation angle in radians.
 * @return A 4x4 matrix representing the rotation around the Y-axis.
 */
t_matrix	matrix_rot_y(double angle);

/**
 * @brief Create a 4x4 matrix representing a rotation around the Z-axis.
 *
 * @param angle The rotation angle in radians.
 * @return A 4x4 matrix representing the rotation around the Z-axis.
 */
t_matrix	matrix_rot_z(double angle);

/**
 * @brief Transform a 3D vector using a 4x4 matrix.
 *
 * @param v The 3D vector to transform.
 * @param m The 4x4 matrix for transformation.
 * @return The transformed vector.
 */
t_vector	dir_matrix(t_vector v, t_matrix m);

/**
 * @brief Transform a 4D vector using a 4x4 matrix.
 *
 * @param v The 4D vector to transform.
 * @param m The 4x4 matrix for transformation.
 * @return The transformed vector.
 */
t_vector	v4_matrix(t_vector4 v, t_matrix m);

#endif