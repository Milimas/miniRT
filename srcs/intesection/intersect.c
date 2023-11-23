/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:21:58 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/11/23 14:17:29 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	intersect(t_ray *ray, t_window *window)
{
	t_object	*objs;

	objs = window->scene.objs;
	while (objs)
	{
		if (objs->type == PLANE)
			plane_int(ray, objs);
		if (objs->type == SPHERE)
			sphere_int(ray, objs);
		if (objs->type == CYLINDER)
			cylinder_int(ray, objs);
		if (objs->type == CONE)
			cone_int(ray, objs);
		objs = objs->next;
	}
}
