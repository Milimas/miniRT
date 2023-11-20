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
	oc = v_sub(ray->origin, cn->position);

	k = tan(cn->angle * M_PI / 180 / 2);
	k = 1 + k * k;
	res.a = 1- k * pow(dot(ray->dir, cn->normal), 2);
	res.b = dot(ray->dir, oc) - k * dot(ray->dir, cn->normal) * dot(oc, cn->normal);
	res.c = dot(oc, oc) - k * pow(dot(oc, cn->normal), 2);

	solve_quadratic(&res, ray->hit.t);

	if (!(res.hit[0] + res.hit[1]))
		return (ray->hit.t);

	double dist = dot(ray->dir, cn->normal) * res.t[0] + dot(oc, cn->normal);
	double dist2 = dot(ray->dir, cn->normal) * res.t[1] + dot(oc, cn->normal);

	res.hit[0] = res.hit[0] && (dist >= -cn->height && dist <= cn->height);
	res.hit[1] = res.hit[1] && (dist2 >= -cn->height && dist2 <= cn->height);

	if (res.hit[0])
	{
		ray->hit.t = res.t[0];
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		ray->hit.normal = norm(v_sub(v_sub(ray->hit.at, cn->position), v_scale(cn->normal, dist * k)));
		ray->hit.uv.x = atan2(ray->hit.normal.x, ray->hit.normal.z) / (2 * M_PI) + .5;
		ray->hit.uv.y = ray->hit.normal.y * .5 + 0.5;
		ray->hit.type = CONE;
	}
	else if (res.hit[1])
	{
		ray->hit.t = res.t[1];
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		ray->hit.normal = norm(v_sub(v_sub(ray->hit.at, cn->position), v_scale(cn->normal, dist2 * k)));
		ray->hit.normal = v_scale(ray->hit.normal, -1);
		ray->hit.uv.x = atan2(ray->hit.normal.x, ray->hit.normal.z) / (2 * M_PI) + .5;
		ray->hit.uv.y = ray->hit.normal.y * .5 + 0.5;
		ray->hit.type = CONE;
	}
	return (ray->hit.t);
}