/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_addition.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:36:36 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/24 23:42:30 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../vector.h"

/**
 * @brief Perform vector addition between two vectors.
 *
 * This function adds two input vectors and returns the resulting vector.
 *
 * @param vector1 The first input vector.
 * @param vector2 The second input vector.
 * @return The vector sum of the two input vectors.
 */
t_vector	vector_addition(t_vector vector1, t_vector vector2)
{
	return ((t_vector){vector1.x + vector2.x, vector1.y + vector2.y});
}
