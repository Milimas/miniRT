/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/11/23 15:51:48 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_hit	set_hit(t_ray *ray, t_quadratic res, t_object *objs)
{
	int	hit;

	if (res.hit[0])
		hit = 0;
	else if (res.hit[1])
		hit = 1;
	else
		return (ray->hit);
	ray->hit.t = res.t[hit];
	ray->hit.obj = objs;
	ray->hit.at = at(*ray, ray->hit.t);
	ray->hit.normal = norm(v_sub(ray->hit.at, objs->sphere->position));
	if (hit)
		ray->hit.normal = v_scale(ray->hit.normal, -1);
	sphere_map(ray);
	ray->hit.type = SPHERE;
	return (ray->hit);
}

double	sphere_int(t_ray *ray, t_object *objs)
{
	t_quadratic	res;
	t_vector	oc;

	oc = v_sub(ray->origin, objs->sphere->position);
	res.a = 1;
	res.b = dot(ray->dir, oc);
	res.c = dot(oc, oc) - pow(objs->sphere->radius, 2);
	solve_quadratic(&res, ray->hit.t);
	set_hit(ray, res, objs);
	return (ray->hit.t);
}
