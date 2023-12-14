/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/12/01 19:17:20 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_hit	set_hit(t_ray *ray, t_quadratic res, t_object *objs)
{
	int	hit;

	if (res.t[0] > ELIPS && res.t[0] < ray->hit.t)
		hit = 0;
	else if (res.t[1] > ELIPS && res.t[1] < ray->hit.t)
		hit = 1;
	else
		return (ray->hit);
	ray->hit.t = res.t[hit];
	ray->hit.obj = objs;
	ray->hit.normal = objs->plane->normal;
	if (hit)
		ray->hit.normal = v_scale(objs->plane->normal, -1);
	ray->hit.at = at(*ray, ray->hit.t);
	ray->hit.type = PLANE;
	plane_map(ray);
	return (ray->hit);
}

double	plane_int(t_ray *ray, t_object *objs)
{
	t_quadratic	res;

	res.delta = dot(ray->dir, objs->plane->normal);
	res.a = dot(v_sub(ray->origin, objs->plane->position), objs->plane->normal);
	if (res.delta == 0 || (res.a * res.delta) > 0)
		return (INFINITY);
	res.t[0] = -res.a / res.delta;
	res.t[1] = res.a / res.delta;
	set_hit(ray, res, objs);
	return (INFINITY);
}
