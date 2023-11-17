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

double	sphere_int(t_ray *ray, t_object *objs)
{
	//! unify the intersection function and norm 
	//! obtimize calculations
	t_quadratic	res;
	t_vector	oc;
	t_sphere	*sphere;

	sphere = objs->sphere;
	oc = v_sub(ray->origin, sphere->position);
	res.a = 1;
	res.b = dot(ray->dir, oc);
	res.c = dot(oc, oc) - pow(sphere->radius, 2);
	solve_quadratic(&res, ray->hit.t);
	if (res.hit[0])
	{
		ray->hit.t = res.t[0];
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		ray->hit.normal = norm(v_sub(ray->hit.at, sphere->position));
		sphere_map(ray);
		return (res.t[0]);
	}
	if (res.hit[1])
	{
		ray->hit.t = res.t[1];
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		ray->hit.normal = norm(v_sub(ray->hit.at, sphere->position));
		sphere_map(ray);
		return (res.t[1]);
	}
	return (0);
}