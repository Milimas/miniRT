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

#include "includes/minirt.h"

void print_vector(char *str, t_vector v)
{
    printf("%s: (%f, %f, %f)\n", str, v.x, v.y, v.z);
}

// t_color	color_scale(t_color color, double scalar)
// {
// 	color.x *= scalar;
// 	color.y *= scalar;
// 	color.z *= scalar;
// 	if (color.x > 0xFF)
// 	color.x = 0xFF;
// 	if (color.y > 0xFF)
// 	color.y = 0xFF;
// 	if (color.z > 0xFF)
// 	color.z = 0xFF;
// 	return (color);
// }


double	max(double min, double max)
{
	if (min > max)
		return (min);
	return (max);
}

// double	min(double min, double max)
// {
// 	if (max > min)
// 		return (min);
// 	return (min);
// }

void	intersect(t_ray *ray, t_window *window)
{
	t_object	*objs;

	objs = window->scene.objs;
	while (objs)
	{
		if (objs->type == PLANE)
			plane_int(ray, objs);
		if (objs->type == SPHERE)
			sphere_int(ray, objs);
		if (objs->type == CYLINDER)
			cylinder_int(ray, objs);
		if (objs->type == CONE)
			cone_int(ray, objs);
		objs = objs->next;
	}
}

void	checkerboard(t_ray *ray)
{
	t_pixel s = ray->hit.uv;
	int x = floor(s.x * 10);
	int y = floor(s.y * 10);
	// int z = floor(s.z * 1/ 0.32);
	int	jump = ((x + y)) % 2;
	if (jump)
		ray->hit.color = vector_scale(ray->hit.color, .1);
}

void	shadow(t_ray *ray, t_window *window)
{
	t_light		*light;

	//! you need to make the colors range from 0 to 1 in all channels
	//! multiply the light with the surface color
	//! for multiple light sources you have to add all light sources then multiply the surface color
	//! https://www.youtube.com/watch?v=lH61rdpJ5v8

	light = window->scene.light;
	t_ray	l_ray;
	l_ray.origin = vector_addition(ray->hit.at, vector_scale(ray->hit.normal, ELIPS));
	l_ray.dir = normalize_vector(vector_subtraction(light->position, l_ray.origin));
	l_ray.hit.t = INFINITY;
	l_ray.hit.obj = NULL;
	// checkerboard(ray);
	intersect(&l_ray, window);
	light_int(&l_ray, window->scene.light);
	ray->hit.color = apply_light(ray->hit.color, ambient(ray, *window->scene.ambient));
	if (l_ray.hit.type != POINT_LIGHT)
		return ;
	t_color diff = {0};
	diff = vector_addition(diff, diffuse(ray, *light));
	// diff = vector_addition(diff, specular(ray, *light));
	ray->hit.color = vector_addition(ray->hit.color, diff);
}

int	render(t_window *window)
{
	t_pixel		p;
	t_camera	*cam;

	p = (t_pixel){-1, -1};
	cam = window->scene.camera;
	clear_mlx_image(window);
	while (++p.y < cam->height)
	{
		p.x = -1;
		while (++p.x < cam->width)
		{
			t_ray r = generate_ray(p, cam);
			intersect(&r, window);
			if (r.hit.t != INFINITY)
			{
				r.hit.color = get_color(*r.hit.obj);
				shadow(&r, window);
				put_pixel(&window->img, (t_pixel){p.x, p.y}, trgb_to_int(vec_to_rgb(r.hit.color)));
			}
		}
	}
	mlx_put_image_to_window(window->mlx.mlx_ptr,
		window->mlx.win_ptr, window->img.img_ptr, 0, 0);
	return (0);
}

void	init_window(t_window *window)
{
	// ft_bzero(&window->scene, sizeof(t_scene));
	window->mlx.mlx_ptr = mlx_init();
	window->mlx.win_ptr = mlx_new_window(window->mlx.mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	window->img.img_ptr = mlx_new_image(window->mlx.mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT);
	window->img.addr = (int *)mlx_get_data_addr(
			window->img.img_ptr,
			&window->img.bits_per_pixel,
			&window->img.size_line,
			&window->img.endian);
}

t_camera	*create_camera(t_camera *cam)
{
	t_vector	tmp;
	cam->look_at = vector_subtraction(cam->look_at, cam->position);
	cam->width = WIN_WIDTH;
	cam->height = WIN_HEIGHT;
	cam->aspect_ratio = (cam->height - 1) / (cam->width - 1);

	t_vector	t = normalize_vector(cam->look_at);
	tmp = normalize_vector((t_vector){0, 1, 0});
	if (t.x != 0 && t.z != 0)
		tmp = normalize_vector((t_vector){t.z, -t.x, t.y});
	print_vector("t", t);
	print_vector("up", tmp);
	t_vector	b = cross_product(t, tmp);
	t_vector	tn = normalize_vector(t);
	t_vector	bn = normalize_vector(b);
	t_vector	vn = cross_product(tn, bn);
	// t_vector	center = vector_addition(cam->position, tn);
	double		gx = tan((cam->fov * M_PI / 180) / 2);
	double		gy = gx * cam->aspect_ratio;
	cam->qx = vector_scale(bn, (2 * gx) / (cam->width - 1));
	cam->qy = vector_scale(vn, (2 * gy) / (cam->height - 1));
	cam->lower_left = vector_subtraction(tn, vector_addition(vector_scale(bn, gx), vector_scale(vn, gy)));
	return (cam);
}

#define K_ESCAPE               0x35

int	close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit(0);
	return (0);
}

int	key_down(int keycode, t_mlx *mlx)
{
	if (keycode == K_ESCAPE)
		close_window(mlx);
	return (0);
}

void	ray_tracing(t_window *window)
{
	init_window(window);
	window->scene.camera = create_camera(window->scene.camera);
	// render(window);
	mlx_loop_hook(window->mlx.mlx_ptr, render, window);
	mlx_key_hook(window->mlx.win_ptr, key_down, &window->mlx);
	mlx_hook(window->mlx.win_ptr, 17, 0, close_window, &window->mlx);
	mlx_loop(window->mlx.mlx_ptr);
}

void print_scene(t_window window)
{
	t_camera cam = *window.scene.camera;
	printf("camera:\n");
	print_vector("position", cam.position);
	print_vector("look_at", cam.look_at);
	printf("fov: %f\n\n", cam.fov);
	t_object *it = window.scene.objs;
	while (it)
	{
		if (it->type == CYLINDER)
		{
			t_cylinder c = *(t_cylinder*)it->cylinder;
			printf("cylinder:\n");
			print_vector("position", c.position);
			print_vector("axis", c.normal);
			printf("radius %f\n", c.radius);
			print_vector("color", c.color);
		}
		if (it->type == PLANE)
		{
			t_plane c = *(t_plane*)it->plane;
			printf("plane:\n");
			print_vector("position", c.position);
			print_vector("axis", c.normal);
			print_vector("color", c.color);
		}
		if (it->type == SPHERE)
		{
			t_sphere c = *(t_sphere*)it->sphere;
			printf("sphere:\n");
			print_vector("position", c.position);
			printf("radius %f\n", c.radius);
			print_vector("color", c.color);
		}
		it = it->next;
	}
}

int	main(int ac, char **av)
{
	char	**file_tab;
	t_window	window;

	if (ac == 2)
	{
		file_tab = read_file(av[1]);
		if (!file_tab)
		{
			printf("Error\nThe .rt file is empty or unexisting\n");
			return (0);
		}
		supervisor(file_tab);
		// scene = ft_calloc(1, sizeof(t_scene));
		init_struct(&window.scene);
		fill_elm(file_tab, &window.scene);
		
		// print_scene(window);

		ray_tracing(&window);
	}
	return (0);
}
