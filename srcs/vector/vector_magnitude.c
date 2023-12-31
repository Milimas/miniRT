/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magnitude.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 23:25:18 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/08/24 23:28:12 by abeihaqi         ###   ########.fr       */
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
double	magnitude(t_vector vector)
{
	return (
		sqrt(vector.x * vector.x
			+ vector.y * vector.y
			+ vector.z * vector.z)
	);
}
