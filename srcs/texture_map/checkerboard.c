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

void	checkerboard(t_ray *ray)
{
	t_pixel	s;
	int		x;
	int		y;
	int		jump;

	s = ray->hit.uv;
	x = floor(s.x * 10);
	y = floor(s.y * 10);
	jump = ((x + y)) % 2;
	if (jump)
		ray->hit.color = v_scale(ray->hit.color, .2);
}

t_color	int_to_color(int trgb)
{
	t_color	color;

	color.x = (trgb >> 16) & 0xFF;
	color.y = (trgb >> 8) & 0xFF;
	color.z = (trgb) & 0xFF;
	return (color);
}

void	bump_map_texture(t_ray *ray)
{
	t_pixel	s;
	t_color	color;

	s = ray->hit.uv;
	// printf("%f, %f\n", s.x, s.y);
	if (s.x > 1 || s.y > 1)
		exit(1);
	s.x = ray->hit.obj->texture.width * fabs(fmod(s.x, 1));
	s.y = ray->hit.obj->texture.height * fabs(fmod(s.y, 1));
	color = int_to_color(get_pixel_color(&ray->hit.obj->texture, s));
	color.x /= 255;
	color.y /= 255;
	color.z /= 255;
	color = norm(v_sub(v_scale(color, 2), (t_color){1, 1, 1}));
	ray->hit.normal = norm(v_sub(ray->hit.normal, color));
	ray->hit.obj->material.ambient = color;
}

void	texture(t_ray *ray)
{
	t_pixel	s;
	t_color	color;

	s = ray->hit.uv;
	s.x = ray->hit.obj->texture.width * fabs(fmod(s.x, 1));
	s.y = ray->hit.obj->texture.height * fabs(fmod(s.y, 1));
	color = int_to_color(get_pixel_color(&ray->hit.obj->texture, s));
	color.x /= 255;
	color.y /= 255;
	color.z /= 255;
	ray->hit.color = apply_light(ray->hit.color, color);
}