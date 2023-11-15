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

t_vector at(t_ray ray, double t)
{
	t_vector	hit;

	hit = vector_addition(ray.origin, vector_scale(ray.dir, t));
	return (hit);
}

t_ray	generate_ray(t_pixel p, t_camera *cam)
{
	t_ray		ray;

	ray.origin = cam->position;
	ray.dir = normalize_vector(vector_addition(cam->lower_left, vector_addition(vector_scale(cam->qx, p.x), vector_scale(cam->qy, p.y))));
	ray.hit.color = (t_color){0x0, 0x0, 0x0};
	ray.hit.t = INFINITY;
	ray.hit.type = NONE;
	ray.hit.obj = NULL;
	ray.p = p;
	ray.aspec = cam->aspect_ratio;
	return (ray);
}