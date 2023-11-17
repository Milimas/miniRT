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

	hit = v_add(ray.origin, v_scale(ray.dir, t));
	return (hit);
}

t_ray	generate_ray(t_pixel p, t_camera *cam)
{
	t_ray		ray;

	ray.origin = cam->position;
	ray.dir = norm(v_add(cam->lower_left, v_add(v_scale(cam->qx, p.x), v_scale(cam->qy, p.y))));
	ray.hit.color = (t_color){0x0, 0x0, 0x0};
	ray.hit.t = INFINITY;
	ray.hit.type = NONE;
	ray.hit.obj = NULL;
	ray.p = p;
	ray.aspec = cam->aspect_ratio;
	return (ray);
}

// t_ray	generate_ray(t_pixel p, t_camera *cam)
// {
// 	t_ray		ray;

// 	// ray.origin = cam->position;
// 	// ray.dir = norm(v_add(cam->lower_left, v_add(v_scale(cam->qx, p.x), v_scale(cam->qy, p.y))));
// 	// ray.hit.color = (t_color){0x0, 0x0, 0x0};
// 	ray.hit.t = INFINITY;
// 	ray.hit.type = NONE;
// 	ray.hit.obj = NULL;
// 	ray.p = p;
// 	ray.aspec = cam->aspect_ratio;
// 	double s = 1 / tan(cam->fov * 0.5 * M_PI / 180);
// 	double n = 0.1;
// 	double f = 100;
// 	t_matrix m;
// 	m.m[0][0] = s;
// 	m.m[1][1] = s;
// 	m.m[2][2] = -f / (f - n);
// 	m.m[2][3] = -1;
// 	m.m[3][2] = -f * n / (f - n);

// 	return (ray);
// }
