/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/11/23 15:06:46 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	cylinder_map(t_ray *ray, double dist)
{
	double		theta;
	t_vector	v;

	v = cross(ray->origin, ray->hit.obj->cylinder->normal);
	v = norm(v);
	theta = acos(dot(v, ray->hit.normal)) / (2 * M_PI);
	ray->hit.uv.x = (theta + .5);
	ray->hit.uv.y = fmod(dist, 1);
}
