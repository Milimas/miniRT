/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/23 20:17:53 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	plane_int(t_ray *ray, t_object *objs)
{
	double		t1;
	t_plane		*plane;
	t_vector	oc;
	double		xv;
	// t_vector	u;
	// t_vector	v;

	plane = objs->plane;
	double	dv = dot_product(ray->dir, plane->normal);
	oc = vector_subtraction(ray->origin, plane->position);
	xv = dot_product(oc, plane->normal);
	if (dv == 0 || (xv * dv) > 0)
		return (INFINITY);
	t1 = -xv / dv;
	if (t1 > ELIPS && t1 < ray->hit.t)
	{
		ray->hit.t = t1;
		ray->hit.obj = objs;
		ray->hit.normal = plane->normal;
		if (dv > 0)
			ray->hit.normal = vector_scale(plane->normal, -1);
		ray->hit.at = at(*ray, ray->hit.t);
		plane_map(ray);
		return (t1);
	}
	return (INFINITY);
}