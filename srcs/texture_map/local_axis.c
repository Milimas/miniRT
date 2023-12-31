/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_axis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:21:58 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/11/23 15:26:55 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_axis	local_axis(t_vector forward)
{
	t_vector	tmp;
	t_axis		axis;

	axis.up = norm(forward);
	tmp = norm((t_vector){0, 1, 0});
	axis.right = norm(cross(tmp, axis.up));
	if (magnitude(axis.right) == 0)
		axis.right = (t_vector){1, 0, 0};
	axis.forward = norm(cross(axis.up, axis.right));
	return (axis);
}
