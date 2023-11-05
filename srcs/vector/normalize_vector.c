/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:36:36 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/24 23:39:58 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Normalize a vector to unit length.
 *
 * This function normalizes an input vector, converting it to a unit vector with
 * the same direction but a length of 1. If the input vector's magnitude is
 * greater than zero, it divides the vector by its magnitude to normalize it.
 * If the magnitude is zero, the original vector is returned unchanged.
 *
 * @param vector The input vector to be normalized.
 * @return The normalized unit vector if the magnitude is greater than zero,
 *         otherwise the original vector.
 */
t_vector	normalize_vector(t_vector vector)
{
	double	magnitude;

	magnitude = vector_magnitude(vector);
	if (magnitude > 0)
		return (vector_division(vector, magnitude));
	printf("error: deviding by 0 in normalize vector\n");
	exit(1);
	return (vector);
}
