/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:33:07 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/08/24 23:10:48 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector.h"

/**
 * @brief Calculate the cross product of two vectors.
 *
 * This function calculates and returns the cross product of two input vectors.
 *
 * @param vector1 The first input vector.
 * @param vector2 The second input vector.
 * @return The cross product vector resulting from the inputs.
 */

t_vector	cross(t_vector vector1, t_vector vector2)
{
	t_vector	result;

	result.x = vector1.y * vector2.z - vector1.z * vector2.y;
	result.y = vector1.z * vector2.x - vector1.x * vector2.z;
	result.z = vector1.x * vector2.y - vector1.y * vector2.x;
	return (result);
}
