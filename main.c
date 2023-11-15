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

double clamp(double value, double min, double max) {
  if (value < min) {
    return min;
  } else if (value > max) {
    return max;
  } else {
    return value;
  }
}

t_vector	vector_scale(t_vector v, double scalar)
{
	v.x *= scalar;
	v.y *= scalar;
	v.z *= scalar;
	return (v);
}

t_color	color_scale(t_color color, double scalar)
{
	color.x *= scalar;
	color.y *= scalar;
	color.z *= scalar;
	if (color.x > 0xFF)
	color.x = 0xFF;
	if (color.y > 0xFF)
	color.y = 0xFF;
	if (color.z > 0xFF)
	color.z = 0xFF;
	return (color);
}

t_color	rgb_to_vec(t_trgb color)
{
	t_color	vec;

	vec.x = (double)color.r / 0xFF;
	vec.y = (double)color.g / 0xFF;
	vec.z = (double)color.b / 0xFF;
	return (vec);
}

t_trgb	vec_to_rgb(t_color vec)
{
	t_trgb	color;

	color.t = 0;
	color.r = clamp(vec.x * 0xFF, 0, 0xFF);
	color.g = clamp(vec.y * 0xFF, 0, 0xFF);
	color.b = clamp(vec.z * 0xFF, 0, 0xFF);
	return (color);
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

t_vector at(t_ray ray, double t)
{
	t_vector	hit;

	hit = vector_addition(ray.origin, vector_scale(ray.dir, t));
	return (hit);
}

void	solve_quadratic(t_quadratic *res, double t)
{
	res->t[0] = INFINITY;
	res->t[1] = INFINITY;
	res->delta = sqrt(res->b * res->b - res->a * res->c);
	if (res->delta < 0)
		return ;
	res->t[0] = (-res->b - res->delta) / res->a;
	res->t[1] = (-res->b + res->delta) / res->a;
	res->hit[0] = (res->t[0] > ELIPS && res->t[0] < t);
	res->hit[1] = (res->t[1] > ELIPS && res->t[1] < t);
}

void sphere_map(t_ray *ray)
{
	double theta;
	double phi;

	theta = atan2(ray->hit.normal.x, ray->hit.normal.z) / (2 * M_PI);
	phi = acos(ray->hit.normal.y);

	ray->hit.uv.x = 1 - (theta + .5);
	ray->hit.uv.y = 1 - phi / M_PI;
}

double	sphere_int(t_ray *ray, t_object *objs)
{
	//! unify the intersection function and norm 
	//! obtimize calculations
	t_quadratic	res;
	t_vector	oc;
	t_sphere	*sphere;

	sphere = objs->sphere;
	oc = vector_subtraction(ray->origin, sphere->position);
	res.a = 1;
	res.b = dot_product(ray->dir, oc);
	res.c = dot_product(oc, oc) - pow(sphere->radius, 2);
	solve_quadratic(&res, ray->hit.t);
	if (res.hit[0])
	{
		ray->hit.t = res.t[0];
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		ray->hit.normal = normalize_vector(vector_subtraction(ray->hit.at, sphere->position));
		sphere_map(ray);
		return (res.t[0]);
	}
	if (res.hit[1])
	{
		ray->hit.t = res.t[1];
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		ray->hit.normal = normalize_vector(vector_addition(ray->hit.at, sphere->position));
		sphere_map(ray);
		return (res.t[1]);
	}
	return (0);
}

double	light_int(t_ray *ray, t_light *light)
{
	double		t;
	t_vector	oc;
	t_light		*l;

	l = light;
	oc = vector_subtraction(l->position, ray->origin);
	t = vector_magnitude(oc);
	if (t > ELIPS && t < ray->hit.t)
	{
		ray->hit.t = t;
		ray->hit.at = at(*ray, t);
		ray->hit.type = POINT_LIGHT;
		return (t);
	}
	return (0);
}

void	cylinder_map(t_ray *ray, double dist)
{
	double theta;

	t_vector	v;

	v = cross_product(ray->origin, ray->hit.obj->cylinder->normal);
	v = normalize_vector(v);
	theta = acos(dot_product(v, ray->hit.normal)) / (2 * M_PI);
	ray->hit.uv.x = 1 - (theta - .5);
	// ray->hit.uv.y = fmod(ray->hit.normal.y, 1);
	ray->hit.uv.y = fmod(dist, 1);
}

double	cylinder_int(t_ray *ray, t_object *objs)
{
	t_quadratic	res;
	t_vector	oc;
	t_cylinder	*cy;


	cy = objs->cylinder;
	oc = vector_subtraction(ray->origin, cy->position);
	objs->oc = oc;
	res.a = 1 - pow(dot_product(ray->dir, cy->normal), 2);
	res.b = dot_product(ray->dir, oc) - dot_product(ray->dir, cy->normal) * dot_product(oc, cy->normal);
	res.c = dot_product(oc, oc) - pow(dot_product(oc, cy->normal), 2) - pow(cy->radius, 2);
	solve_quadratic(&res, ray->hit.t);

	if (!(res.hit[0] + res.hit[1]))
		return (ray->hit.t);

	double dist = dot_product(ray->dir, cy->normal) * res.t[0] + dot_product(oc, cy->normal);
	double dist2 = dot_product(ray->dir, cy->normal) * res.t[1] + dot_product(oc, cy->normal);

	res.hit[0] *= (dist >= 0 && dist <= cy->height);
	res.hit[1] *= (dist2 >= 0 && dist2 <= cy->height);

	if (res.hit[0])
	{
		ray->hit.t = res.t[0];
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		ray->hit.normal = normalize_vector(vector_subtraction(ray->hit.at, vector_addition(cy->position, vector_scale(cy->normal, dist))));
		cylinder_map(ray, dist);
	}
	else if (res.hit[1])
	{
		ray->hit.t = res.t[1];
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		ray->hit.normal = normalize_vector(vector_subtraction(ray->hit.at, vector_addition(cy->position, vector_scale(cy->normal, dist2))));
		ray->hit.normal = vector_scale(ray->hit.normal, -1);
		cylinder_map(ray, dist2);
	}
	return (ray->hit.t);
}


double	cone_int(t_ray *ray, t_object *objs)
{
	t_quadratic	res;
	t_vector	oc;
	t_cone	*cn;
	double		k;


	cn = objs->cone;
	oc = vector_subtraction(ray->origin, cn->position);

	k = tan(cn->angle * M_PI / 180 / 2);
	// printf("%f\n", k);
	k = 1 + k * k;
	res.a = 1- k * pow(dot_product(ray->dir, cn->normal), 2);
	res.b = dot_product(ray->dir, oc) - k * dot_product(ray->dir, cn->normal) * dot_product(oc, cn->normal);
	res.c = dot_product(oc, oc) - k * pow(dot_product(oc, cn->normal), 2);

	solve_quadratic(&res, ray->hit.t);

	if (!(res.hit[0] + res.hit[1]))
		return (ray->hit.t);

	double dist = dot_product(ray->dir, cn->normal) * res.t[0] + dot_product(oc, cn->normal);
	double dist2 = dot_product(ray->dir, cn->normal) * res.t[1] + dot_product(oc, cn->normal);

	res.hit[0] *= (dist >= -cn->height && dist <= cn->height);
	res.hit[1] *= (dist2 >= -cn->height && dist2 <= cn->height);

	if (res.hit[0])
	{
		ray->hit.t = res.t[0];
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		// N = nrm( P-C - (1+k*k)*V*m )
		ray->hit.normal = normalize_vector(vector_addition(ray->hit.at, vector_subtraction(cn->position, vector_scale(vector_scale(cn->normal, k), dist))));
		// ray->hit.normal = vector_scale(ray->hit.normal, -1);
		ray->hit.uv.x = atan2(ray->hit.normal.x, ray->hit.normal.z) / (2 * M_PI) + .5;
		ray->hit.uv.y = ray->hit.normal.y * .5 + 0.5;
	}
	else if (res.hit[1])
	{
		ray->hit.t = res.t[1];
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		// N = nrm( P-C - (1+k*k)*V*m )
		ray->hit.normal = normalize_vector(vector_subtraction(ray->hit.at, vector_subtraction(cn->position, vector_scale(vector_scale(cn->normal, k), dist2))));
		ray->hit.uv.x = atan2(ray->hit.normal.x, ray->hit.normal.z) / (2 * M_PI) + .5;
		ray->hit.uv.y = ray->hit.normal.y * .5 + 0.5;
	}
	return (ray->hit.t);
}

void	plane_map(t_ray *ray)
{
	// check for y != 1
	ray->hit.uv.x = fmod(ray->hit.at.x, 1);
	ray->hit.uv.y = fmod(ray->hit.at.z, 1);
}

double	plane_int(t_ray *ray, t_object *objs)
{
	double		t1;
	t_plane		*plane;
	t_vector	oc;
	double		xv;
	// t_vector	u;
	// t_vector	v;

	plane = objs->plane;
	double	dv = dot_product(ray->dir, plane->normal);
	oc = vector_subtraction(ray->origin, plane->position);
	xv = dot_product(oc, plane->normal);
	if (dv == 0 || (xv * dv) > 0)
		return (INFINITY);
	t1 = -xv / dv;
	if (t1 > ELIPS && t1 < ray->hit.t)
	{
		ray->hit.t = t1;
		ray->hit.obj = objs;
		ray->hit.normal = plane->normal;
		if (dv > 0)
			ray->hit.normal = vector_scale(plane->normal, -1);
		ray->hit.at = at(*ray, ray->hit.t);
		plane_map(ray);
		return (t1);
	}
	return (INFINITY);
}

t_color	get_color(t_object obj)
{
	if (obj.type == SPHERE)
		return (obj.sphere->color);
	if (obj.type == PLANE)
		return (obj.plane->color);
	if (obj.type == CYLINDER)
		return (obj.cylinder->color);
	if (obj.type == CONE)
		return (obj.cone->color);
	return ((t_color){0xFF, 0x0, 0xFF});
}

double	max(double min, double max)
{
	if (min > max)
		return (min);
	return (max);
}

double	min(double min, double max)
{
	if (max > min)
		return (min);
	return (min);
}

t_color	apply_light(t_color surface, t_color light)
{
	t_color	res;

	res.x = clamp(surface.x * light.x, 0, 1);
	res.y = clamp(surface.y * light.y, 0, 1);
	res.z = clamp(surface.z * light.z, 0, 1);
	return (res);
}

t_color	ambient(t_ray *ray, t_ambient_light amb)
{
	if (amb.ratio < 0 || amb.ratio > 1)
		return ((t_color){0});
	(void)ray;
	return (vector_scale(amb.color, amb.ratio));
}

t_color	diffuse(t_ray *ray, t_light light)
{
	if (light.ratio < 0 || light.ratio > 1)
		return ((t_color){0});
	t_vector l = normalize_vector(vector_subtraction(light.position, ray->hit.at));
	t_vector n = ray->hit.normal;
	double nl = dot_product(n, l);
	if (nl < 0)
		return ((t_color){0});
	return (vector_scale(light.color, max(0, nl) * light.ratio));
}

t_color	specular(t_ray *ray, t_light light)
{
	if (light.ratio < 0 || light.ratio > 1)
		return ((t_color){0});
	t_vector v = normalize_vector(vector_scale(ray->dir, -1));
	t_vector l = normalize_vector(vector_subtraction(light.position, ray->hit.at));
	t_vector r = normalize_vector(vector_subtraction(vector_scale(ray->hit.normal, 2 * dot_product(ray->hit.normal, l)), l));
	// t_vector n = ray->hit.normal;
	// double nl = dot_product(n, l);
	// if (nl < 0)
	// 	return ((t_color){0});
	return (vector_scale(light.color, light.ratio * pow(max(0, dot_product(r, v)), 32)));
}

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
	checkerboard(ray);
	intersect(&l_ray, window);
	light_int(&l_ray, window->scene.light);
	ray->hit.color = apply_light(ray->hit.color, ambient(ray, *window->scene.ambient));
	if (l_ray.hit.type != POINT_LIGHT)
		return ;
	t_color diff = {0};
	diff = vector_addition(diff, diffuse(ray, *light));
	diff = vector_addition(diff, specular(ray, *light));
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
	render(window);
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


