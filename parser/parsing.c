/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouarrak <rouarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:38:57 by rimouarrak        #+#    #+#             */
/*   Updated: 2023/11/20 20:53:52 by rouarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	check_rgb(char **rgb)
{
	double	r;
	double	g;
	double	b;

	r = (double)ft_atoi(rgb[0]) / 0xFF;
	g = (double)ft_atoi(rgb[1]) / 0xFF;
	b = (double)ft_atoi(rgb[2]) / 0xFF;
	if (! (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255))
	{
		printf("Error\nThe rgb values should be between 0 and 255\n");
		exit (0);
	}
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

void	fill_a(char	*str, t_scene *scene)
{
	char	**tab;
	char	**rgb;

	tab = ft_split(str, ' ');
	if (!(str_to_double(tab[1]) >= 0 && str_to_double(tab[1]) <= 1))
	{
		printf("Error\nAmbient lighting ratio should be in range [0.0,1.0]\n");
		exit(0);
	}
	scene->ambient->ratio = str_to_double(tab[1]);
	rgb = ft_split(tab[2], ',');
	check_rgb(rgb);
	scene->ambient->color.x = (double)ft_atoi(rgb[0]) / 0xFF;
	scene->ambient->color.y = (double)ft_atoi(rgb[1]) / 0xFF;
	scene->ambient->color.z = (double)ft_atoi(rgb[2]) / 0xFF;
	free_split(tab);
	free_split(rgb);
}

void	fill_c(char	*str, t_scene *scene)
{
	char	**tab;
	char	**pos;
	char	**ort;

	tab = ft_split(str, ' ');
	pos = ft_split(tab[1], ',');
	scene->camera->position.x = str_to_double(pos[0]);
	scene->camera->position.y = str_to_double(pos[1]);
	scene->camera->position.z = str_to_double(pos[2]);
	ort = ft_split(tab[2], ',');
	scene->camera->look_at.x = str_to_double(ort[0]);
	scene->camera->look_at.y = str_to_double(ort[1]);
	scene->camera->look_at.z = str_to_double(ort[2]);
	scene->camera->fov = ft_atoi(tab[3]);
	free_split(tab);
	free_split(pos);
	free_split(ort);
}

void	fill_l(char	*str, t_scene *scene)
{
	char	**tab;
	char	**pos;
	char	**rgb;

	tab = ft_split(str, ' ');
	pos = ft_split(tab[1], ',');
	scene->light->position.x = str_to_double(pos[0]);
	scene->light->position.y = str_to_double(pos[1]);
	scene->light->position.z = str_to_double(pos[2]);
	scene->light->ratio = str_to_double(tab[2]);
	rgb = ft_split(tab[3], ',');
	check_rgb(rgb);
	scene->light->color.x = (double)ft_atoi(rgb[0]) / 0xFF;
	scene->light->color.y = (double)ft_atoi(rgb[1]) / 0xFF;
	scene->light->color.z = (double)ft_atoi(rgb[2]) / 0xFF;
	free_split(tab);
	free_split(rgb);
	free_split(pos);
}

void	fill_sl(char	*str, t_scene *scene)
{
	char		**tab;
	char		**pos;
	char		**rgb;
	t_object	*object;
	t_light		*light;

	tab = ft_split(str, ' ');
	pos = ft_split(tab[1], ',');
	object = ft_calloc(sizeof(t_object), 1);
	light = ft_calloc(sizeof(t_light), 1);
	light->position.x = str_to_double(pos[0]);
	light->position.y = str_to_double(pos[1]);
	light->position.z = str_to_double(pos[2]);
	light->ratio = str_to_double(tab[2]);
	rgb = ft_split(tab[3], ',');
	check_rgb(rgb);
	light->color.x = (double)ft_atoi(rgb[0]) / 0xFF;
	light->color.y = (double)ft_atoi(rgb[1]) / 0xFF;
	light->color.z = (double)ft_atoi(rgb[2]) / 0xFF;
	object->spot = light;
	append_object(&scene->spots, object);
	free_split(tab);
	free_split(rgb);
	free_split(pos);
}

void	fill_pl(char	*str, t_scene *scene)
{
	t_plane		*plane;
	t_object	*object;

	plane = pl_new(str);
	plane->normal = norm(plane->normal);
	object = ft_calloc(sizeof(t_object), 1);
	object->plane = plane;
	object->type = PLANE;
	object->next = NULL;
	append_object(&scene->objs, object);
}

void	fill_sp(char	*str, t_scene *scene)
{
	t_sphere	*sphere;
	t_object	*object;

	sphere = sp_new(str);
	object = ft_calloc(sizeof(t_object), 1);
	object->sphere = sphere;
	object->type = SPHERE;
	object->next = NULL;
	append_object(&scene->objs, object);
}

void	fill_cy(char	*str, t_scene *scene)
{
	t_cylinder	*cylinder;
	t_object	*object;

	cylinder = cy_new(str);
	cylinder->normal = norm(cylinder->normal);
	object = ft_calloc(sizeof(t_object), 1);
	object->cylinder = cylinder;
	object->type = CYLINDER;
	object->next = NULL;
	append_object(&scene->objs, object);
}

void	fill_cn(char	*str, t_scene *scene)
{
	t_cone		*cone;
	t_object	*object;

	cone = cn_new(str);
	cone->normal = norm(cone->normal);
	object = ft_calloc(sizeof(t_object), 1);
	object->cone = cone;
	object->type = CONE;
	object->next = NULL;
	append_object(&scene->objs, object);
}

void	fill_elm(char	**tab, t_scene *scene)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], "A", 1))
			fill_a(tab[i], scene);
		else if (!ft_strncmp(tab[i], "C", 1))
			fill_c(tab[i], scene);
		else if (!ft_strncmp(tab[i], "L", 1))
			fill_l(tab[i], scene);
		else if (!ft_strncmp(tab[i], "pl", 2))
			fill_pl(tab[i], scene);
		else if (!ft_strncmp(tab[i], "sp", 2))
			fill_sp(tab[i], scene);
		else if (!ft_strncmp(tab[i], "cy", 2))
			fill_cy(tab[i], scene);
		else if (!ft_strncmp(tab[i], "cn", 2))
			fill_cn(tab[i], scene);
		else if (!ft_strncmp(tab[i], "sl", 2))
			fill_sl(tab[i], scene);
		i++;
	}
}

void	init_struct(t_scene *scene)
{
	scene->ambient = ft_calloc(1, sizeof(t_ambient_light));
	scene->camera = ft_calloc(1, sizeof(t_camera));
	scene->light = ft_calloc(1, sizeof(t_light));
}
