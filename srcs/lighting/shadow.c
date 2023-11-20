
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
	t_object	*obj;
	t_ray	l_ray;

	obj = window->scene.spots;
	ft_bzero(&ray->hit.obj->material, sizeof(t_material));
	# ifdef CHECKER
		// checkerboard(ray);
	# endif
	l_ray.origin = v_add(ray->hit.at, v_scale(ray->hit.normal, ELIPS));
	while (obj)
	{
		light = obj->spot;
		l_ray.dir = norm(v_sub(light->position, l_ray.origin));
		l_ray.hit.t = INFINITY;
		l_ray.hit.obj = NULL;
		intersect(&l_ray, window);
		light_int(&l_ray, light);
		if (l_ray.hit.type == POINT_LIGHT)
		{
			ray->hit.obj->material.diffuse = v_add(ray->hit.obj->material.diffuse, diffuse(ray, *light));
			ray->hit.obj->material.specular = v_add(ray->hit.obj->material.specular, specular(ray, *light));
		}
		obj = obj->next;
	}
	ray->hit.obj->material.ambient = ambient(ray, *window->scene.ambient);
	ray->hit.color = v_add(
		ray->hit.obj->material.ambient,
		v_add(
			apply_light(ray->hit.color, ray->hit.obj->material.diffuse),
			apply_light(ray->hit.color, ray->hit.obj->material.specular)
		)
	);
}

// void	shadow(t_ray *ray, t_window *window)
// {
// 	t_light		*light;
// 	t_ray	l_ray;

// 	light = window->scene.light;
// 	ft_bzero(&ray->hit.obj->material, sizeof(t_material));
// 	# ifdef CHECKER
// 		// checkerboard(ray);
// 	# endif
// 	l_ray.origin = v_add(ray->hit.at, v_scale(ray->hit.normal, ELIPS));
// 	l_ray.dir = norm(v_sub(light->position, l_ray.origin));
// 	l_ray.hit.t = INFINITY;
// 	l_ray.hit.obj = NULL;
// 	intersect(&l_ray, window);
// 	light_int(&l_ray, light);
// 	if (l_ray.hit.type == POINT_LIGHT)
// 	{
// 		ray->hit.obj->material.diffuse = v_add(ray->hit.obj->material.diffuse, diffuse(ray, *light));
// 		ray->hit.obj->material.specular = v_add(ray->hit.obj->material.specular, specular(ray, *light));
// 	}
// 	ray->hit.obj->material.ambient = ambient(ray, *window->scene.ambient);
// 	ray->hit.color = v_add(
// 		ray->hit.obj->material.ambient,
// 		v_add(
// 			apply_light(ray->hit.color, ray->hit.obj->material.diffuse),
// 			apply_light(ray->hit.color, ray->hit.obj->material.specular)
// 		)
// 	);
// }