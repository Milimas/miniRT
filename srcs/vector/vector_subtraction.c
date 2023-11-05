/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_subtraction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:36:36 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/24 23:41:21 by aminebeihaq      ###   ########.fr       */
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
t_vector	vector_subtraction(t_vector vector1, t_vector vector2)
{
	return ((t_vector){vector1.x - vector2.x, vector1.y - vector2.y, vector1.z - vector2.z});
}
