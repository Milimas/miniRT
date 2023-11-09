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
	// ray.hit.color = mix_trgb(ray.hit.color, ambient->color, ambient->ratio);
	// ray.hit.color = mix_trgb(ray.hit.color, ambient->color, ambient->ratio);
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
	t1 = (-b - delta) / 2;
	if (t1 > ELIPS && t1 < ray->hit.t)
	{
		ray->hit.t = t1;
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		ray->hit.normal = normalize_vector(vector_subtraction(ray->hit.at, s->position));
		return (t1);
	}
	t2 = (-b + delta) / 2;
	if (t2 > ELIPS && t2 < ray->hit.t)
	{
		ray->hit.t = t2;
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		ray->hit.normal = normalize_vector(vector_subtraction(ray->hit.at, s->position));
		return (t2);
	}
	return (0);
}

double	light_int(t_ray *ray, t_object *objs)
{
	double		t;
	t_vector	oc;
	t_light		*l;

	l = objs->obj;
	oc = vector_subtraction(l->position, ray->origin);
	t = vector_magnitude(oc);
	if (t > ELIPS && t < ray->hit.t)
	{
		// printf("hit point light\n");
		ray->hit.t = t;
		ray->hit.at = at(*ray, t);
		ray->hit.obj = objs;
		return (t);
	}
	return (0);
}

double	closest_t(double t1, double t2)
{
	if (t1 <= ELIPS && t2 <= ELIPS)
		return (0);
	if (t1 > t2 && t2 > ELIPS)
		return (t2);
	if (t2 > t1 && t1 > ELIPS)
		return (t1);
	return (0);
}

double	cylinder_int(t_ray *ray, t_object *objs)
{
	double		t1;
	double		t2;
	double		a;
	double		b;
	double		c;
	t_vector	oc;
	t_cylinder	*cy;


	cy = objs->obj;
	oc = vector_subtraction(ray->origin, cy->position);

	a = dot_product(ray->dir, ray->dir) - pow(dot_product(ray->dir, cy->normal), 2);
	b = dot_product(ray->dir, oc) - dot_product(ray->dir, cy->normal) * dot_product(oc, cy->normal);
	c = dot_product(oc, oc) - pow(dot_product(oc, cy->normal), 2) - pow(cy->radius, 2);

	double delta = sqrt(b*b - a * c);
	if (delta < 0)
		return (0);
	t1 = (-b - delta) / a;
	t2 = (-b + delta) / a;

	double dist = dot_product(ray->dir, cy->normal) * t1 + dot_product(oc, cy->normal);
	if (t1 < ray->hit.t && t1 > ELIPS && dist >= 0 && dist <= cy->height)
	{
		ray->hit.t = t1;
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		ray->hit.normal = normalize_vector(vector_subtraction(ray->hit.at, vector_subtraction(cy->position, vector_scale(cy->normal, dist))));
		return (t1);
	}
	double dist2 = dot_product(ray->dir, cy->normal) * t2 + dot_product(oc, cy->normal);
	if (t2 < ray->hit.t && t2 > ELIPS && dist2 >= 0 && dist2 <= cy->height)
	{
		ray->hit.t = t2;
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		ray->hit.normal = normalize_vector(vector_subtraction(ray->hit.at, vector_subtraction(cy->position, vector_scale(cy->normal, dist2))));
		ray->hit.normal = vector_scale(ray->hit.normal, -1);
		return (t2);
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
		if (t1 > ELIPS && t1 < ray->hit.t)
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

int	get_shading(t_ray *ray, t_light light)
{
	// t_vector	v;
	t_vector	l;
	t_trgb		color;

	color = get_color(*ray->hit.obj);
	// v = vector_scale(normalize_vector(ray->dir), -1);
	l = normalize_vector(vector_subtraction(light.position, ray->hit.at));
	// double	dist = vector_magnitude(vector_subtraction(light.position, ray->hit.at));
	if (dot_product(ray->hit.normal, l) < 0)
		return ray->hit.color.t;
	// double	intensity = light.ratio * (1.0 / dist * dist);
	double intensity = clamp(fmax(0, dot_product(ray->hit.normal, l)), 0, 1);
	color = mix_trgb(color, light.color, light.ratio);
	return (ray->hit.color.t * (1 - intensity));
	// ray->hit.color = mix_trgb(ray->hit.color, color, intensity);
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
		objs = objs->next;
	}
	// if (ray->hit.t == INFINITY)
	// 	return ;
}

void	shadow(t_ray *ray, t_window *window)
{
	t_object	*lights;
	t_light		*light;

	lights = window->scene.lights;
	ray->hit.color.t = 0xFF * (1 - ((t_ambient_light *)window->scene.ambient->obj)->ratio);
	while (lights)
	{
		light = lights->obj;
		t_ray	l_ray;
		l_ray.origin = vector_addition(ray->hit.at, vector_scale(ray->hit.normal, 0.01));
		l_ray.dir = normalize_vector(vector_subtraction(light->position, ray->hit.at));
		l_ray.hit.t = INFINITY;
		l_ray.hit.obj = NULL;
		intersect(&l_ray, window);
		light_int(&l_ray, window->scene.lights);
		if (l_ray.hit.obj && l_ray.hit.obj->type == POINT_LIGHT)
			ray->hit.color.t = get_shading(ray, *light);
		lights = lights->next;
	}
}

// void	shadow(t_ray *ray, t_window *window)
// {
// 	t_object	*lights;
// 	t_light		*light;

// 	lights = window->scene.lights;
// 	while (lights)
// 	{
// 		light = lights->obj;
// 		t_ray	l_ray;
// 		l_ray.origin = vector_addition(ray->hit.at, vector_scale(ray->hit.normal, 0.0001));
// 		l_ray.dir = normalize_vector(vector_subtraction(l_ray.origin, light->position));
// 		l_ray.hit.t = INFINITY;
// 		intersect(&l_ray, window);
// 		ray->hit.color.t = 0x80;
// 		if (l_ray.hit.t != INFINITY && l_ray.hit.obj != ray->hit.obj)
// 		{
// 			get_shading(ray, *((t_light *)lights->obj));
// 			// if (dot_product(l_ray.dir, ray->hit.normal) > 1)
// 			// printf("%f\n", dot_product(l_ray.dir, ray->hit.normal));
// 			// ray->hit.color.t = 0;
// 		}
// 		// else if (l_ray.hit.obj != ray->hit.obj)
// 		// {
// 		// 	ray->hit.color.t = 0x80;
// 		// }
// 		lights = lights->next;
// 	}
// }

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
			{
				r.hit.color = get_color(*r.hit.obj);
				shadow(&r, window);
				put_pixel(&window->img, (t_pixel){p.x, p.y}, trgb_to_int(r.hit.color));
			}
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
	cam->position = (t_vector){0, 5, 0};
	cam->look_at = (t_vector){0, 0, 0};
	cam->look_at = vector_subtraction(cam->look_at, cam->position);
	print_vector("cam look at", cam->look_at);
	cam->look_at = normalize_vector(cam->look_at);
	cam->fov = 90;
	cam->width = WIN_WIDTH;
	cam->height = WIN_HEIGHT;
	cam->aspect_ratio = (cam->height - 1) / (cam->width - 1);

	t_vector	t = normalize_vector(cam->look_at);
	t_vector	b = cross_product(t, (t_vector){0, 1, 0.5});
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
	plane->normal = normalize_vector(normal);
	plane->color = color;
	object->obj = plane;
	object->type = PLANE;
	return (object);
}

t_object	*create_cylinder(t_vector origin, t_vector normal, double radius, double height, t_trgb color)
{
	t_object		*object;
	t_cylinder		*cylinder;

	object = ft_calloc(sizeof(t_object), 1);
	cylinder = ft_calloc(sizeof(t_cylinder), 1);
	cylinder->position = origin;
	cylinder->normal = normalize_vector(normal);
	cylinder->radius = radius;
	cylinder->height = height;
	cylinder->color = color;
	object->obj = cylinder;
	object->type = CYLINDER;
	return (object);
}

t_object	*create_ambient_light(double ratio, t_trgb color)
{
	t_object		*object;
	t_ambient_light	*ambient;

	object = ft_calloc(sizeof(t_object), 1);
	ambient = ft_calloc(sizeof(t_ambient_light), 1);
	ambient->ratio = ratio;
	ambient->color = color;
	object->obj = ambient;
	object->type = AMBIENT_LIGHT;
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
	append_object(&window.scene.ambient, create_ambient_light(.2, (t_trgb){0x0, 0x80, 0x80, 0x80}));
	append_object(&window.scene.lights, create_light((t_vector){0, 11, 0}, .5, (t_trgb){0x0, 0xFF, 0xFF, 0xFF}));
	// append_object(&window.scene.objs, create_sphere((t_vector){2, 0, 0}, 1, (t_trgb){0x00, 0xFF, 0xFF, 0xFF}));
	append_object(&window.scene.objs, create_plane((t_vector){0, 0, 0}, (t_vector){0, -1, 0}, (t_trgb){0x00, 0x80, 0xFF, 0x80}));
	append_object(&window.scene.objs, create_plane((t_vector){0, 10, 0}, (t_vector){0, 1, 0}, (t_trgb){0x00, 0x80, 0xFF, 0x80}));
	append_object(&window.scene.objs, create_sphere((t_vector){2, 1, 1}, 1, (t_trgb){0x00, 0xFF, 0xFF, 0xFF}));
	append_object(&window.scene.objs, create_sphere((t_vector){2, 2, 1}, .1, (t_trgb){0x00, 0x80, 0x80, 0x80}));
	append_object(&window.scene.objs, create_sphere((t_vector){-2, 2, 1}, .1, (t_trgb){0x00, 0x80, 0x80, 0x80}));
	append_object(&window.scene.objs, create_sphere((t_vector){-2, 1, 1}, 1, (t_trgb){0x00, 0xFF, 0xFF, 0xFF}));
	append_object(&window.scene.objs, create_cylinder((t_vector){0, -0.5, 0}, (t_vector){0, 1, 1}, 5, 1, (t_trgb){0x00, 0xFF, 0x50, 0x10}));
	render(&window);
	// mlx_loop_hook(window.mlx.mlx_ptr, render, &window);
	mlx_loop(window.mlx.mlx_ptr);
}
