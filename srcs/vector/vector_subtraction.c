/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_sub.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:36:36 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/08/24 23:41:21 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector.h"

/**
 * @brief Perform vector subtraction between two vectors.
 *
 * This function subtracts the second input vector from the first input vector
 * and returns the resulting vector.
 *
 * @param vector1 The first input vector.
 * @param vector2 The second input vector.
 * @return The vector difference between the two input vectors.
 */
t_vector	v_sub(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}
