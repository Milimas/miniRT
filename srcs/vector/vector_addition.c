/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:36:36 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/08/24 23:42:30 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector.h"

/**
 * @brief Perform vector addition between two vectors.
 *
 * This function adds two input vectors and returns the resulting vector.
 *
 * @param vector1 The first input vector.
 * @param vector2 The second input vector.
 * @return The vector sum of the two input vectors.
 */
t_vector	v_add(t_vector vector1, t_vector vector2)
{
	return ((t_vector){
		vector1.x + vector2.x,
		vector1.y + vector2.y,
		vector1.z + vector2.z
	});
}
