/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/11/24 18:22:38 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

#define HIT_INSIDE	1
#define HIT_OUTSIDE	0

static void	set_dist(t_quadratic *res, t_ray *ray, t_object *objs)
{
	res->dist[0] = dot(ray->dir, objs->cone->normal)
		* res->t[0] + dot(objs->oc, objs->cone->normal);
	res->dist[1] = dot(ray->dir, objs->cone->normal)
		* res->t[1] + dot(objs->oc, objs->cone->normal);
}

static t_hit	set_hit(t_ray *ray, t_quadratic res, t_object *objs)
{
	int	hit;

	set_dist(&res, ray, objs);
	res.hit[0] = (res.hit[0] && (res.dist[0] >= 0
				&& res.dist[0] <= objs->cone->height));
	res.hit[1] = (res.hit[1] && (res.dist[1] >= 0
				&& res.dist[1] <= objs->cone->height));
	if (res.hit[0])
		hit = 0;
	else if (res.hit[1])
		hit = 1;
	else
		return (ray->hit);
	ray->hit.t = res.t[hit];
	ray->hit.obj = objs;
	ray->hit.at = at(*ray, ray->hit.t);
	ray->hit.normal = norm(v_sub(v_sub(ray->hit.at, objs->cone->position),
				v_scale(objs->cone->normal, res.dist[hit] * res.k)));
	if (hit)
		ray->hit.normal = v_scale(ray->hit.normal, -1);
	cone_map(ray, res.dist[hit]);
	ray->hit.type = CONE;
	return (ray->hit);
}

double	cone_int(t_ray *ray, t_object *objs)
{
	t_quadratic	res;

	objs->oc = v_sub(ray->origin, objs->cone->position);
	res.k = tan(objs->cone->angle * M_PI / 180 / 2);
	res.k = 1 + res.k * res.k;
	res.a = 1 - res.k * pow(dot(ray->dir, objs->cone->normal), 2);
	res.b = dot(ray->dir, objs->oc) - res.k * dot(ray->dir, objs->cone->normal)
		* dot(objs->oc, objs->cone->normal);
	res.c = dot(objs->oc, objs->oc) - res.k
		* pow(dot(objs->oc, objs->cone->normal), 2);
	solve_quadratic(&res, ray->hit.t);
	set_hit(ray, res, objs);
	return (ray->hit.t);
}
