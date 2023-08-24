/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_product.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:33:07 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/24 23:10:48 by aminebeihaq      ###   ########.fr       */
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

t_vector	cross_product(t_vector vector1, t_vector vector2)
{
	t_vector	result;

	result.x = vector1.y * vector1.z - vector1.z * vector1.y;
	result.x = vector1.z * vector1.x - vector1.x * vector1.z;
	result.x = vector1.x * vector1.y - vector1.y * vector1.x;
	return (result);
}
