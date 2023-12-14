/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:21:58 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/11/30 13:36:46 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	is_shadow(t_ray *ray, t_light *light, t_window *window)
{
	t_ray	l_ray;

	l_ray.origin = v_add(ray->hit.at, v_scale(ray->hit.normal, ELIPS));
	l_ray.dir = norm(v_sub(light->position, l_ray.origin));
	l_ray.hit.t = INFINITY;
	l_ray.hit.obj = NULL;
	intersect(&l_ray, window);
	light_int(&l_ray, light);
	if (ray->hit.obj == l_ray.hit.obj)
		return (0);
	return (l_ray.hit.type != POINT_LIGHT);
}

void	phong(t_ray *ray, t_light *light, t_window *window)
{
	if (is_shadow(ray, light, window))
		return ;
	ray->hit.obj->material.diffuse = v_add(ray->hit.obj->material.diffuse,
			diffuse(ray, *light));
	ray->hit.obj->material.specular = v_add(ray->hit.obj->material.specular,
			specular(ray, *light));
}

void	mix_light(t_color	*surface, t_material material)
{
	*surface = apply_light(*surface, v_add(
				material.ambient,
				v_add(material.diffuse, material.specular)));
}

void	shadow(t_ray *ray, t_window *window)
{
	t_light		*light;
	t_object	*obj;

	obj = window->scene.spots;
	ray->hit.color = get_color(*ray->hit.obj);
	ft_bzero(&ray->hit.obj->material, sizeof(t_material));
	if (ray->hit.obj->checkerboard)
		checkerboard(ray);
	if (ray->hit.obj->height_map.img_ptr)
		bump_map_texture(ray);
	ray->hit.obj->material.ambient = ambient(ray, *window->scene.ambient);
	phong(ray, window->scene.light, window);
	while (obj)
	{
		light = obj->spot;
		phong(ray, light, window);
		obj = obj->next;
	}
	mix_light(&ray->hit.color, ray->hit.obj->material);
}
