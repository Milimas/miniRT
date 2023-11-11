/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_magnitude.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 23:25:18 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/24 23:28:12 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../includes/vector.h"

/**
 * @brief Calculate the magnitude (length) of a 2D vector.
 *
 * This function calculates and returns the magnitude (length) of the input 2D
 * vector.
 *
 * @param vector The input 2D vector.
 * @return The magnitude of the input 2D vector.
 */
double	vector_magnitude(t_vector vector)
{
	return (sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z));
}
