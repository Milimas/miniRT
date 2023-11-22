
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:21:58 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/24 22:32:37 by aminebeihaq      ###   ########.fr       */
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