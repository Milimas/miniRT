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

t_ray	generate_ray(t_pixel p, t_camera *cam)
{
	t_ray		ray;

	// generating ray start here
	ray.origin = cam->position;
	ray.dir = normalize_vector(vector_addition(cam->lower_left, vector_addition(vector_scale(cam->qx, p.x), vector_scale(cam->qy, p.y))));
	ray.hit.color = (t_color){0x0, 0x0, 0x0};
	ray.hit.t = INFINITY;
	ray.hit.type = NONE;
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
		// printf("hit point light\n");
		ray->hit.t = t;
		ray->hit.at = at(*ray, t);
		ray->hit.type = POINT_LIGHT;
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
	double dist2 = dot_product(ray->dir, cy->normal) * t2 + dot_product(oc, cy->normal);

	if ((dist < 0 || dist > cy->height) && (dist2 < 0 || dist2 > cy->height))
		return (0);

	if (t1 > ELIPS && t1 < ray->hit.t && dist >= 0 && dist <= cy->height)
	{
		ray->hit.t = t1;
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		ray->hit.normal = normalize_vector(vector_subtraction(ray->hit.at, vector_addition(cy->position, vector_scale(cy->normal, dist))));
	}
	if (t2 > ELIPS && t2 < ray->hit.t && dist2 >= 0 && dist2 <= cy->height)
	{
		ray->hit.t = t2;
		ray->hit.obj = objs;
		ray->hit.at = at(*ray, ray->hit.t);
		ray->hit.normal = normalize_vector(vector_subtraction(ray->hit.at, vector_addition(cy->position, vector_scale(cy->normal, dist2))));
		ray->hit.normal = vector_scale(ray->hit.normal, -1);
	}
	return (ray->hit.t);
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

double	ambient(t_ray *ray, t_ambient_light amb)
{
	if (amb.ratio < 0 && amb.ratio > 1)
		return (0);
	(void)ray;
	return (amb.ratio);
}

double	diffuse(t_ray *ray, t_light light)
{
	if (!ray->not_shadow)
		return (0);
	if (light.ratio < 0 && light.ratio > 1)
		return (0);
	t_vector l = normalize_vector(vector_subtraction(light.position, ray->hit.at));
	t_vector n = ray->hit.normal;
	double nl = dot_product(n, l);
	if (nl < 0)
		return (0);
	double id = light.ratio * max(0, nl);
	return (id);
}

double	specular(t_ray *ray, t_light light)
{
	if (!ray->not_shadow)
		return (0);
	if (light.ratio < 0 && light.ratio > 1)
		return (0);
	t_vector v = vector_scale(normalize_vector(ray->dir), -1);
	t_vector l = normalize_vector(vector_subtraction(light.position, ray->hit.at));
	t_vector n = ray->hit.normal;
	t_vector r = normalize_vector(vector_subtraction(vector_scale(ray->hit.normal, 2 * dot_product(ray->hit.normal, l)), l));
	double nl = dot_product(n, l);
	if (nl < 0)
		return (0);
	double is = light.ratio * pow(dot_product(r, v), 1);
	if (is < 0)
		return (0);
	return (is);
}

// t_color	deffuse(t_ray *ray, t_light light)
// {
// 	t_vector	v;
// 	t_vector	l;
// 	t_vector	r;
// 	t_vector	n;
// 	t_trgb		color;

// 	color = get_color(*ray->hit.obj);
// 	v = vector_scale(normalize_vector(ray->dir), -1);
// 	l = normalize_vector(vector_subtraction(light.position, ray->hit.at));
// 	r = normalize_vector(vector_subtraction(vector_scale(ray->hit.normal, 2 * dot_product(ray->hit.normal, l)), l));
// 	n = ray->hit.normal;

// 	double kd = light.ratio;
// 	double ks = 1;
// 	double ka = ray->illumination;

// 	double id = 1;
// 	double is = 2;
// 	double ia = ka;
// 	double shininess = 1;

// 	// double specular = pow(dot_product(v, r), 0);
// 	// double diffuse = light.ratio * max(0, dot_product(ray->hit.normal, l));
// 	// ray->hit.color.t = 0xFF * (1 - ray->illumination);
// 	// ray->hit.color.t = 0xFF * (1 - clamp(diffuse + ray->illumination + specular, 0, 1));
// 	double ip = ka * ia * (kd * clamp(dot_product(l, n), 0, 1) * id + ks * pow(clamp(dot_product(r, v), 0, 1), shininess) * is);
// 	// printf("ip = %f", ip);
// 	// ray->hit.color = 0xFF * (1 - ip);
// 	return (ray->hit.color);
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
		objs = objs->next;
	}
}

void	shadow(t_ray *ray, t_window *window)
{
	t_light		*light;

	light = window->scene.light;
	t_ray	l_ray;
	l_ray.origin = vector_addition(ray->hit.at, vector_scale(ray->hit.normal, ELIPS));
	l_ray.dir = normalize_vector(vector_subtraction(light->position, l_ray.origin));
	l_ray.hit.t = INFINITY;
	l_ray.hit.obj = NULL;
	ray->not_shadow = 0;
	intersect(&l_ray, window);
	light_int(&l_ray, window->scene.light);
	if (l_ray.hit.type == POINT_LIGHT)
		ray->not_shadow = 1;
	// ray->hit.color = diffuse(ray, *light);
	// ray->hit.color = specular(ray, *light);
	
	double i = ambient(ray, *window->scene.ambient) + diffuse(ray, *light) + specular(ray, *light);
	i = clamp(i, 0, 1);
	// printf("i: %f\n", i);
	ray->hit.color = color_scale(ray->hit.color, i);
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
			r.illumination = window->scene.ambient->ratio;
			intersect(&r, window);
			if (r.hit.t != INFINITY)
			{
				t_trgb tmp = get_color(*r.hit.obj);
				r.hit.color.x = tmp.r;
				r.hit.color.y = tmp.g;
				r.hit.color.z = tmp.b;
				shadow(&r, window);
				tmp.t = 0;
				tmp.r = r.hit.color.x;
				tmp.g = r.hit.color.y;
				tmp.b = r.hit.color.z;
				put_pixel(&window->img, (t_pixel){p.x, p.y}, trgb_to_int(tmp));
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
	cam->look_at = vector_subtraction(cam->look_at, cam->position);
	print_vector("cam look at", cam->look_at);
	cam->look_at = normalize_vector(cam->look_at);
	cam->width = WIN_WIDTH;
	cam->height = WIN_HEIGHT;
	cam->aspect_ratio = (cam->height - 1) / (cam->width - 1);

	t_vector	t = normalize_vector(cam->look_at);
	t_vector	b = cross_product(t, normalize_vector(vector_addition(t, (t_vector){0, 1, 0})));
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

t_light	*create_light(t_vector origin, double ratio, t_trgb color)
{
	t_light		*light;

	light = ft_calloc(sizeof(t_light), 1);
	light->position = origin;
	light->ratio = ratio;
	light->color = color;
	return (light);
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

t_ambient_light	*create_ambient_light(double ratio, t_trgb color)
{
	t_ambient_light	*ambient;

	ambient = ft_calloc(sizeof(t_ambient_light), 1);
	ambient->ratio = ratio;
	ambient->color = color;
	return (ambient);
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
	// window->scene.ambient = create_ambient_light(0.22, (t_trgb){0x0, 0x80, 0x80, 0x80});
	// window->scene.light = create_light((t_vector){0, 10, 0}, .5, (t_trgb){0x0, 0xFF, 0xFF, 0xFF});
	// append_object(&window->scene.objs, create_plane((t_vector){0, 0, 0}, (t_vector){0, -1, 0}, (t_trgb){0x00, 0xFF, 0xFF, 0xFF}));
	// append_object(&window->scene.objs, create_sphere((t_vector){-2, .5, 1}, .25, (t_trgb){0x00, 0x80, 0x80, 0xFF}));
	// append_object(&window->scene.objs, create_cylinder((t_vector){0, .5, 0}, (t_vector){-1, 0, 0}, .5, 2, (t_trgb){0x00, 0xFF, 0x50, 0x10}));
	render(window);
	// mlx_loop_hook(window->mlx.mlx_ptr, render, window);
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
			t_cylinder c = *(t_cylinder*)it->obj;
			printf("cylinder:\n");
			print_vector("position", c.position);
			print_vector("axis", c.normal);
			printf("radius %f\n", c.radius);
			printf("color %d, %d, %d, %d\n\n", c.color.t, c.color.r, c.color.g, c.color.b);
		}
		if (it->type == PLANE)
		{
			t_plane c = *(t_plane*)it->obj;
			printf("plane:\n");
			print_vector("position", c.position);
			print_vector("axis", c.normal);
			printf("color %d, %d, %d, %d\n\n", c.color.t, c.color.r, c.color.g, c.color.b);
		}
		if (it->type == SPHERE)
		{
			t_sphere c = *(t_sphere*)it->obj;
			printf("sphere:\n");
			print_vector("position", c.position);
			printf("radius %f\n", c.radius);
			printf("color %d, %d, %d, %d\n\n", c.color.t, c.color.r, c.color.g, c.color.b);
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
		
		print_scene(window);

		ray_tracing(&window);
	}
	return (0);
}


