/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/11/23 17:31:18 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vector	at(t_ray ray, double t)
{
	t_vector	hit;

	hit = v_add(ray.origin, v_scale(ray.dir, t));
	return (hit);
}

t_ray	generate_ray(t_pixel p, t_camera *cam)
{
	t_ray		ray;

	ray.origin = cam->position;
	ray.dir = norm(v_add(cam->lower_left,
				v_add(v_scale(cam->u, p.x), v_scale(cam->v, p.y))));
	ray.hit.color = (t_color){0x0, 0x0, 0x0};
	ray.hit.t = INFINITY;
	ray.hit.type = NONE;
	ray.hit.obj = NULL;
	return (ray);
}
