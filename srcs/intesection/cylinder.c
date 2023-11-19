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

double	cylinder_int(t_ray *ray, t_object *objs)
{
	t_quadratic	res;
	t_vector	oc;
	t_cylinder	*cy;


	cy = objs->cylinder;
	oc = v_sub(ray->origin, cy->position);
	objs->oc = oc;
	res.a = 1 - pow(dot(ray->dir, cy->normal), 2);
	res.b = dot(ray->dir, oc) - dot(ray->dir, cy->normal) * dot(oc, cy->normal);
	res.c = dot(oc, oc) - pow(dot(oc, cy->normal), 2) - pow(cy->radius, 2);
	solve_quadratic(&res, ray->hit.t);

	if (!(res.hit[0] + res.hit[1]))
		return (ray->hit.t);

	double dist = dot(ray->dir, cy->normal) * res.t[0] + dot(oc, cy->normal);
	double dist2 = dot(ray->dir, cy->normal) * res.t[1] + dot(oc, cy->normal);

	res.hit[0] = res.hit[0] && (dist >= 0 && dist <= cy->height);
	res.hit[1] = res.hit[1] && (dist2 >= 0 && dist2 <= cy->height);

	if (res.hit[0])
	{
		ray->hit.t = res.t[0];
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		ray->hit.normal = norm(v_sub(ray->hit.at, v_add(cy->position, v_scale(cy->normal, dist))));
		ray->hit.type = CYLINDER;
		cylinder_map(ray, dist);
	}
	else if (res.hit[1])
	{
		ray->hit.t = res.t[1];
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		ray->hit.normal = norm(v_sub(ray->hit.at, v_add(cy->position, v_scale(cy->normal, dist2))));
		ray->hit.normal = v_scale(ray->hit.normal, -1);
		ray->hit.type = CYLINDER;
		cylinder_map(ray, dist2);
	}
	return (ray->hit.t);
}