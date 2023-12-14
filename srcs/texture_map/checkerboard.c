/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/12/01 20:00:20 by abeihaqi         ###   ########.fr       */
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
	x = floor(s.x * CHECKER_SIZE);
	y = floor(s.y * CHECKER_SIZE);
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

t_color	bump_norm(t_object *obj, t_pixel s)
{
	t_color		color;
	t_vector	normal;
	t_color		fx;
	t_color		fy;

	color = int_to_color(get_pixel_color(&obj->height_map, s));
	color = v_div(color, 0xFF);
	fx = int_to_color(get_pixel_color(&obj->height_map,
				(t_pixel){s.x + 1, s.y}));
	fx = v_div(fx, 0xFF);
	fy = int_to_color(get_pixel_color(&obj->height_map,
				(t_pixel){s.x, s.y + 1}));
	fy = v_div(fy, 0xFF);
	fx = v_sub(fx, color);
	fy = v_sub(fy, color);
	fx = v_scale(fx, HEIGHT_SCALER);
	fy = v_scale(fy, HEIGHT_SCALER);
	normal.x = -fx.x / sqrt(pow(fx.x, 2) + pow(fy.y, 2) + 1);
	normal.y = fy.y / sqrt(pow(fx.x, 2) + pow(fy.y, 2) + 1);
	normal.z = 1 / sqrt(pow(fx.x, 2) + pow(fy.y, 2) + 1);
	return (norm(normal));
}

void	bump_map_texture(t_ray *ray)
{
	t_pixel		s;
	t_vector	normal;

	s = ray->hit.uv;
	if (s.x > 1 || s.y > 1)
		exit(1);
	s.x = ray->hit.obj->height_map.width * fabs(fmod(s.x, 1));
	s.y = ray->hit.obj->height_map.height * fabs(fmod(s.y, 1));
	normal = bump_norm(ray->hit.obj, s);
	ray->hit.normal = v_add(ray->hit.normal, normal);
	ray->hit.normal = norm(ray->hit.normal);
}

void	texture(t_ray *ray)
{
	t_pixel	s;
	t_color	color;

	s = ray->hit.uv;
	s.x = ray->hit.obj->texture.width * fabs(fmod(s.x, 1));
	s.y = ray->hit.obj->texture.height * fabs(fmod(s.y, 1));
	color = int_to_color(get_pixel_color(&ray->hit.obj->texture, s));
	color = v_scale(color, 0xFF);
	ray->hit.color = apply_light(ray->hit.color, color);
}
