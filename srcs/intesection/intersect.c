/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:21:58 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/11/23 14:17:29 by abeihaqi         ###   ########.fr       */
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
