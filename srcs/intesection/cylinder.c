/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/11/23 14:13:27 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	set_dist(t_quadratic *res, t_ray *ray, t_object *objs)
{
	res->dist[0] = dot(ray->dir, objs->cylinder->normal)
		* res->t[0] + dot(objs->oc, objs->cylinder->normal);
	res->dist[1] = dot(ray->dir, objs->cylinder->normal)
		* res->t[1] + dot(objs->oc, objs->cylinder->normal);
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
	ray->hit.normal = norm(v_sub(ray->hit.at, v_add(objs->cylinder->position,
					v_scale(objs->cylinder->normal, res.dist[hit]))));
	if (hit)
		ray->hit.normal = v_scale(ray->hit.normal, -1);
	cylinder_map(ray, res.dist[hit]);
	ray->hit.type = CYLINDER;
	return (ray->hit);
}

double	cylinder_int(t_ray *ray, t_object *objs)
{
	t_quadratic	res;

	objs->oc = v_sub(ray->origin, objs->cylinder->position);
	res.a = 1 - pow(dot(ray->dir, objs->cylinder->normal), 2);
	res.b = dot(ray->dir, objs->oc) - dot(ray->dir, objs->cylinder->normal)
		* dot(objs->oc, objs->cylinder->normal);
	res.c = dot(objs->oc, objs->oc)
		- pow(dot(objs->oc, objs->cylinder->normal), 2)
		- pow(objs->cylinder->radius, 2);
	solve_quadratic(&res, ray->hit.t);
	set_hit(ray, res, objs);
	return (ray->hit.t);
}
