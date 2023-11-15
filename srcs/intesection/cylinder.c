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
	oc = vector_subtraction(ray->origin, cy->position);
	objs->oc = oc;
	res.a = 1 - pow(dot_product(ray->dir, cy->normal), 2);
	res.b = dot_product(ray->dir, oc) - dot_product(ray->dir, cy->normal) * dot_product(oc, cy->normal);
	res.c = dot_product(oc, oc) - pow(dot_product(oc, cy->normal), 2) - pow(cy->radius, 2);
	solve_quadratic(&res, ray->hit.t);

	if (!(res.hit[0] + res.hit[1]))
		return (ray->hit.t);

	double dist = dot_product(ray->dir, cy->normal) * res.t[0] + dot_product(oc, cy->normal);
	double dist2 = dot_product(ray->dir, cy->normal) * res.t[1] + dot_product(oc, cy->normal);

	res.hit[0] *= (dist >= 0 && dist <= cy->height);
	res.hit[1] *= (dist2 >= 0 && dist2 <= cy->height);

	if (res.hit[0])
	{
		ray->hit.t = res.t[0];
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		ray->hit.normal = normalize_vector(vector_subtraction(ray->hit.at, vector_addition(cy->position, vector_scale(cy->normal, dist))));
		cylinder_map(ray, dist);
	}
	else if (res.hit[1])
	{
		ray->hit.t = res.t[1];
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		ray->hit.normal = normalize_vector(vector_subtraction(ray->hit.at, vector_addition(cy->position, vector_scale(cy->normal, dist2))));
		ray->hit.normal = vector_scale(ray->hit.normal, -1);
		cylinder_map(ray, dist2);
	}
	return (ray->hit.t);
}