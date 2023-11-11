/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_product.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:33:07 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/24 22:56:48 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector.h"

/**
 * @brief Calculate the dot product of two vectors.
 *
 * This function calculates and returns the dot product of two input vectors.
 *
 * @param vector1 The first input vector.
 * @param vector2 The second input vector.
 * @return The dot product of the two input vectors.
 */
double	dot_product(t_vector vector1, t_vector vector2)
{
	return ((vector1.x * vector2.x)
		+ (vector1.y * vector2.y)
		+ (vector1.z * vector2.z));
}
