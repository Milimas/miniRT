/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/11/25 16:55:21 by aminebeihaq      ###   ########.fr       */
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
	t_color	fx;
	t_color	fy;

	s = ray->hit.uv;
	if (s.x > 1 || s.y > 1)
		exit(1);
	s.x = ray->hit.obj->texture.width * fabs(fmod(s.x, 1));
	s.y = ray->hit.obj->texture.height * fabs(fmod(s.y, 1));
	color = int_to_color(get_pixel_color(&ray->hit.obj->texture, s));
	color = v_div(color, 0xFF);
	fx = int_to_color(get_pixel_color(&ray->hit.obj->texture, (t_pixel){s.x + 1, s.y}));
	fx = v_div(fx, 0xFF);
	fy = int_to_color(get_pixel_color(&ray->hit.obj->texture, (t_pixel){s.x, s.y + 1}));
	fy = v_div(fy, 0xFF);
	fx = v_sub(fx, color);
	fy = v_sub(fy, color);
	fx = v_scale(fx, 10);
	fy = v_scale(fy, 10);
	t_vector normal;
	normal.x = fx.x / sqrt(pow(fx.x, 2) + pow(fy.y, 2) + 1);
	normal.y = fy.y / sqrt(pow(fx.x, 2) + pow(fy.y, 2) + 1);
	normal.z = 1 / sqrt(pow(fx.x, 2) + pow(fy.y, 2) + 1);
	ray->hit.normal = v_add(ray->hit.normal, normal);
	// ray->hit.normal.x = ray->hit.normal.x / color.x;
	// ray->hit.normal.y = ray->hit.normal.y / color.y;
	// ray->hit.normal.z = ray->hit.normal.z / color.z;
	// color = norm(v_sub(v_scale(color, 2), (t_color){1, 1, 1}));
	// ray->hit.normal = norm(v_add(ray->hit.normal, color));
	// ray->hit.color = color;
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
