/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/11/24 19:01:14 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	cylinder_map(t_ray *ray, double dist)
{
	double		theta;
	t_vector	v;

	v = cross(ray->hit.obj->local.right, ray->hit.normal);
	v = norm(v);
	theta = acos(dot(ray->hit.obj->local.right, ray->hit.normal));
	if (v.y > 0)
		theta = 2 * M_PI - theta;
	theta /= (2 * M_PI);
	ray->hit.uv.x = 1 - (theta);
	ray->hit.uv.y = 1 - dist / ray->hit.obj->cylinder->height;
}
