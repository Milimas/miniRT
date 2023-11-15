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

double	cone_int(t_ray *ray, t_object *objs)
{
	t_quadratic	res;
	t_vector	oc;
	t_cone	*cn;
	double		k;


	cn = objs->cone;
	oc = vector_subtraction(ray->origin, cn->position);

	k = tan(cn->angle * M_PI / 180 / 2);
	k = 1 + k * k;
	res.a = 1- k * pow(dot_product(ray->dir, cn->normal), 2);
	res.b = dot_product(ray->dir, oc) - k * dot_product(ray->dir, cn->normal) * dot_product(oc, cn->normal);
	res.c = dot_product(oc, oc) - k * pow(dot_product(oc, cn->normal), 2);

	solve_quadratic(&res, ray->hit.t);

	if (!(res.hit[0] + res.hit[1]))
		return (ray->hit.t);

	double dist = dot_product(ray->dir, cn->normal) * res.t[0] + dot_product(oc, cn->normal);
	double dist2 = dot_product(ray->dir, cn->normal) * res.t[1] + dot_product(oc, cn->normal);

	res.hit[0] *= (dist >= -cn->height && dist <= cn->height);
	res.hit[1] *= (dist2 >= -cn->height && dist2 <= cn->height);

	if (res.hit[0])
	{
		ray->hit.t = res.t[0];
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		ray->hit.normal = normalize_vector(vector_addition(ray->hit.at, vector_subtraction(cn->position, vector_scale(vector_scale(cn->normal, k), dist))));
		ray->hit.uv.x = atan2(ray->hit.normal.x, ray->hit.normal.z) / (2 * M_PI) + .5;
		ray->hit.uv.y = ray->hit.normal.y * .5 + 0.5;
	}
	else if (res.hit[1])
	{
		ray->hit.t = res.t[1];
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		ray->hit.normal = normalize_vector(vector_subtraction(ray->hit.at, vector_subtraction(cn->position, vector_scale(vector_scale(cn->normal, k), dist2))));
		ray->hit.uv.x = atan2(ray->hit.normal.x, ray->hit.normal.z) / (2 * M_PI) + .5;
		ray->hit.uv.y = ray->hit.normal.y * .5 + 0.5;
	}
	return (ray->hit.t);
}