
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:21:58 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/24 22:32:37 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

//! you need to make the colors range from 0 to 1 in all channels
//! multiply the light with the surface color
//! for multiple light sources you have to add all light sources then multiply the surface color
//! https://www.youtube.com/watch?v=lH61rdpJ5v8
void	shadow(t_ray *ray, t_window *window)
{
	t_light		*light;

	light = window->scene.light;
	t_ray	l_ray;
	l_ray.origin = v_add(ray->hit.at, v_scale(ray->hit.normal, ELIPS));
	l_ray.dir = norm(v_sub(light->position, l_ray.origin));
	l_ray.hit.t = INFINITY;
	l_ray.hit.obj = NULL;
# ifdef CHECKER
	checkerboard(ray);
# endif
	intersect(&l_ray, window);
	light_int(&l_ray, window->scene.light);
	ray->hit.color = apply_light(ray->hit.color, ambient(ray, *window->scene.ambient));
	if (l_ray.hit.type != POINT_LIGHT)
		return ;
	t_color diff = {0};
	diff = v_add(diff, diffuse(ray, *light));
	diff = v_add(diff, specular(ray, *light));
	ray->hit.color = v_add(ray->hit.color, diff);
}