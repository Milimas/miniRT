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

t_vector	vector_scale(t_vector v, double scalar)
{
	v.x *= scalar;
	v.y *= scalar;
	v.z *= scalar;
	return (v);
}

t_ray	generate_ray(t_pixel p, t_camera *cam)
{
	t_ray		ray;

	// generating ray start here
	ray.origin = cam->position;
	ray.dir = normalize_vector(vector_addition(cam->lower_left, vector_addition(vector_scale(cam->qx, p.x), vector_scale(cam->qy, p.y))));
	ray.hit.color = (t_trgb){0x0, 0x0, 0x0, 0x0};
	ray.hit.t = INFINITY;
	return (ray);
}

t_vector at(t_ray ray, double t)
{
	t_vector	hit;

	hit = vector_addition(ray.origin, vector_scale(ray.dir, t));
	return (hit);
}

double	sphere_int(t_ray *ray, t_object *objs)
{
	double		t1;
	double		t2;
	double		b;
	double		c;
	t_vector	oc;
	t_sphere	*s;

	s = objs->obj;
	oc = vector_subtraction(ray->origin, s->position);
	b = 2 * dot_product(ray->dir, oc);
	c = dot_product(oc, oc) - s->radius;
	double delta = sqrt(pow(b, 2) - 4 * c);
	if (delta < 0)
		return (0);
	// if (delta == 0)
	// 	return (-b / 2);
	t1 = (-b + delta) / 2;
	t2 = (-b - delta) / 2;
	if (t2 < t1 && t2 > 0)
		t1 = t2;
	if (t1 > 0 && t1 < ray->hit.t)
	{
		ray->hit.t = t1;
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		ray->hit.normal = normalize_vector(vector_subtraction(ray->hit.at, s->position));
		return (t1);
	}
	return (0);
}

double	plane_int(t_ray *ray, t_object *objs)
{
	double		t1;
	t_plane		*plane;
	t_vector	pl;

	plane = objs->obj;
	double	denom = dot_product(plane->normal, ray->dir);
	if (denom > 1e-6)
	{
		pl = vector_subtraction(plane->position, ray->origin);
		t1 = dot_product(pl, plane->normal) / denom;
		if (t1 > 0 && t1 < ray->hit.t)
		{
			ray->hit.t = t1;
			ray->hit.obj = objs;
			ray->hit.normal = vector_scale(plane->normal, -1);
			ray->hit.at = at(*ray, ray->hit.t);
			return (t1);
		}
	}
	return (0);
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

t_trgb	get_color(t_object obj)
{
	if (obj.type == SPHERE)
		return (((t_sphere *)obj.obj)->color);
	if (obj.type == PLANE)
		return (((t_plane *)obj.obj)->color);
	if (obj.type == CYLINDER)
		return (((t_cylinder *)obj.obj)->color);
	return ((t_trgb){0x0, 0xFF, 0x0, 0xFF});
}

void	get_shading(t_ray *ray, t_light light)
{
	t_vector	v;
	t_vector	l;
	t_trgb		color;

	color = get_color(*ray->hit.obj);
	v = vector_scale(normalize_vector(ray->dir), -1);
	l = normalize_vector(vector_subtraction(light.position, ray->hit.at));
	double	dist = vector_magnitude(vector_subtraction(light.position, ray->hit.at));
	if (dot_product(ray->hit.normal, l) < 0)
		return ;
	double	intensity = light.ratio * (1.0 / dist * dist);
	intensity = clamp(intensity * fmax(0, dot_product(ray->hit.normal, l)), 0, 1);
	color = mix_trgb(color, light.color, light.ratio);
	color.t = 0xFF * (1 - intensity);
	ray->hit.color = mix_trgb(ray->hit.color, color, intensity);
}

void	intersect(t_ray *ray, t_window *window)
{
	t_object	*objs;

	objs = window->scene.objs;
	while (objs)
	{
		if (objs->type == SPHERE)
			sphere_int(ray, objs);
		if (objs->type == PLANE)
		{
			plane_int(ray, objs);
		}
		objs = objs->next;
	}
	if (ray->hit.t == INFINITY)
		return ;
}

void	shadow(t_ray *ray, t_window *window)
{
	t_object	*lights;
	t_light		*light;

	lights = window->scene.lights;
	while (lights)
	{
		light = lights->obj;
		t_ray	l_ray;
		l_ray.origin = light->position;
		l_ray.dir = normalize_vector(vector_subtraction(ray->hit.at, light->position));
		l_ray.hit.t = INFINITY;
		intersect(&l_ray, window);
		if (l_ray.hit.obj == ray->hit.obj)
			get_shading(ray, *((t_light *)lights->obj));
		lights = lights->next;
	}
}

int	render(t_window *window)
{
	t_pixel		p;
	t_camera	*cam;

	p = (t_pixel){-1, -1};
	cam = window->scene.cameras->obj;
	clear_mlx_image(window);
	while (++p.y < cam->height)
	{
		p.x = -1;
		while (++p.x < cam->width)
		{
			t_ray r = generate_ray(p, cam);
			intersect(&r, window);
			if (r.hit.t != INFINITY)
				shadow(&r, window);
			put_pixel(&window->img, (t_pixel){p.x, p.y}, trgb_to_int(r.hit.color));
		}
	}
	mlx_put_image_to_window(window->mlx.mlx_ptr,
		window->mlx.win_ptr, window->img.img_ptr, 0, 0);
	return (0);
}

void	init_window(t_window *window)
{
	ft_bzero(&window->scene, sizeof(t_scene));
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

void	init_cam(t_camera *cam)
{
	cam->look_at = (t_vector){0, 0, 1};
	cam->look_at = normalize_vector(cam->look_at);
	cam->position = (t_vector){0, 0, 0};
	cam->fov = 60;
	cam->width = WIN_WIDTH;
	cam->height = WIN_HEIGHT;
	cam->aspect_ratio = (cam->height - 1) / (cam->width - 1);

	t_vector	t = vector_subtraction(cam->look_at, cam->position);
	t_vector	b = cross_product(t, (t_vector){0, 1, 0});
	t_vector	tn = normalize_vector(t);
	t_vector	bn = normalize_vector(b);
	t_vector	vn = cross_product(tn, bn);
	// t_vector	center = vector_addition(cam->position, tn);
	double		gx = tan((cam->fov * M_PI / 180) / 2);
	double		gy = gx * cam->aspect_ratio;
	cam->qx = vector_scale(bn, (2 * gx) / (cam->width - 1));
	cam->qy = vector_scale(vn, (2 * gy) / (cam->height - 1));
	cam->lower_left = vector_subtraction(tn, vector_addition(vector_scale(bn, gx), vector_scale(vn, gy)));
}

t_object	*create_camera()
{
	t_object	*object;

	object = ft_calloc(sizeof(t_object), 1);
	object->obj = ft_calloc(sizeof(t_camera), 1);
	init_cam(object->obj);
	object->type = CAMERA;
	object->next = NULL;
	return (object);
}

t_object	*create_light(t_vector origin, double ratio, t_trgb color)
{
	t_object	*object;
	t_light		*light;

	object = ft_calloc(sizeof(t_object), 1);
	light = ft_calloc(sizeof(t_light), 1);
	light->position = origin;
	light->ratio = ratio;
	light->color = color;
	object->obj = light;
	object->type = POINT_LIGHT;
	return (object);
}

t_object	*create_sphere(t_vector origin, double radius, t_trgb color)
{
	t_object	*object;
	t_sphere	*sphere;

	object = ft_calloc(sizeof(t_object), 1);
	sphere = ft_calloc(sizeof(t_sphere), 1);
	sphere->position = origin;
	sphere->radius = radius;
	sphere->color = color;
	object->obj = sphere;
	object->type = SPHERE;
	return (object);
}

t_object	*create_plane(t_vector origin, t_vector normal, t_trgb color)
{
	t_object	*object;
	t_plane		*plane;

	object = ft_calloc(sizeof(t_object), 1);
	plane = ft_calloc(sizeof(t_plane), 1);
	plane->position = origin;
	plane->normal = normal;
	plane->color = color;
	object->obj = plane;
	object->type = PLANE;
	return (object);
}

t_object	*last_obj(t_object *head)
{
	while (head && head->next)
		head = head->next;
	return (head);
}

void	append_object(t_object **head, t_object *new)
{
	if (!*head)
		*head = new;
	else
		last_obj(*head)->next = new;
}


int	main( void )
{
	t_window	window;

	init_window(&window);
	append_object(&window.scene.cameras, create_camera());
	append_object(&window.scene.lights, create_light((t_vector){100, 100, 10}, 0.5, (t_trgb){0x0, 0xFF, 0xFF, 0xFF}));
	append_object(&window.scene.lights, create_light((t_vector){-100, 100, 10}, 0.5, (t_trgb){0x0, 0xFF, 0xFF, 0xFF}));
	append_object(&window.scene.lights, create_light((t_vector){0, 100, 10}, 0.5, (t_trgb){0x0, 0xFF, 0xFF, 0xFF}));
	append_object(&window.scene.objs, create_sphere((t_vector){-1, 2, 10}, 1, (t_trgb){0x00, 0xFF, 0xFF, 0xFF}));
	append_object(&window.scene.objs, create_sphere((t_vector){1, 2, 10}, 1, (t_trgb){0x00, 0xFF, 0xFF, 0x0}));
	append_object(&window.scene.objs, create_plane((t_vector){0, -1, 0}, (t_vector){0, -1, 0}, (t_trgb){0x00, 0xFF, 0xFF, 0xFF}));
	// append_object(&window.scene.objs, create_sphere((t_vector){3, 0, 10}, 1, (t_trgb){0x00, 0x0, 0xFF, 0x0}));
	render(&window);
	// mlx_loop_hook(window.mlx.mlx_ptr, render, &window);
	mlx_loop(window.mlx.mlx_ptr);
}
