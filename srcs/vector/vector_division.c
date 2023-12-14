/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_div.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 23:28:55 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/08/24 23:35:06 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector.h"

/**
 * @brief Divide a vector by a scalar value.
 *
 * This function divides each component of the input vector by the provided
 * scalar value.
 *
 * @param vector The input vector to be divided.
 * @param scalar The scalar value to divide the vector components by.
 * @return The resulting vector after division by the scalar.
 */
t_vector	v_div(t_vector vector, double scalar)
{
	return (
		(t_vector){vector.x / scalar, vector.y / scalar, vector.z / scalar});
}
