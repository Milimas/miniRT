/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/11/24 18:36:17 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	cone_map(t_ray *ray, double dist)
{
	double		theta;
	t_vector	v;
	t_vector	n;

	n = norm(cross(ray->hit.obj->cone->normal, ray->hit.normal));
	n = norm(cross(n, ray->hit.obj->cone->normal));
	v = cross(ray->hit.obj->local.right, n);
	v = norm(v);
	theta = acos(dot(ray->hit.obj->local.right, n));
	if (v.y > 0)
		theta = 2 * M_PI - theta;
	theta /= (2 * M_PI);
	ray->hit.uv.x = 1 - (theta);
	ray->hit.uv.y = 1 - fabs(dist / ray->hit.obj->cone->height);
}
