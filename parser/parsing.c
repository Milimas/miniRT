/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimouarrak <rimouarrak@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:38:57 by rimouarrak        #+#    #+#             */
/*   Updated: 2023/09/10 19:46:36 by rimouarrak       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

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
	scene->ambient->ratio = str_to_double(tab[1]);
	rgb = ft_split(tab[2], ',');
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
	scene->light->color.x = (double)ft_atoi(rgb[0]) / 0xFF;
	scene->light->color.y = (double)ft_atoi(rgb[1]) / 0xFF;
	scene->light->color.z = (double)ft_atoi(rgb[2]) / 0xFF;
	free_split(tab);
	free_split(rgb);
	free_split(pos);
}

void	fill_pl(char	*str, t_scene *scene)
{
	t_plane		*plane;
	t_object	*object;

	plane = pl_new(str);
	plane->normal = normalize_vector(plane->normal);
	object = ft_calloc(sizeof(t_object), 1);
	object->obj = plane;
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
	object->obj = sphere;
	object->type = SPHERE;
	object->next = NULL;
	append_object(&scene->objs, object);
}

void	fill_cy(char	*str, t_scene *scene)
{
	t_cylinder	*cylinder;
	t_object	*object;

	cylinder = cy_new(str);
	cylinder->normal = normalize_vector(cylinder->normal);
	object = ft_calloc(sizeof(t_object), 1);
	object->obj = cylinder;
	object->type = CYLINDER;
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
		i++;
	}
}

void	init_struct(t_scene *scene)
{
	scene->ambient = ft_calloc(1, sizeof(t_ambient_light));
	scene->camera = ft_calloc(1, sizeof(t_camera));
	scene->light = ft_calloc(1, sizeof(t_light));
	// scene->planes = ft_calloc(1, sizeof(t_plane));
	// scene->spheres = ft_calloc(1, sizeof(t_sphere));
	// scene->cylinders = ft_calloc(1, sizeof(t_cylinder));
}

// int	main(int ac, char **av)
// {
// 	char	**file_tab;
// 	t_scene	*scene;

// 	if (ac == 2)
// 	{
// 		file_tab = read_file(av[1]);
// 		if (!file_tab)
// 		{
// 			printf("Error\nThe .rt file is empty or unexisting\n");
// 			return (0);
// 		}
// 		supervisor(file_tab);
// 		scene = ft_calloc(1, sizeof(t_scene));
// 		init_struct(scene);
// 		fill_elm(file_tab, scene);
// 		system("leaks nanort");
// 		// printf("res ,, %f\n", scene->cylinders->diameter);
// 		// printf("res ,, %f\n", scene->cylinders->next->diameter);
// 		// printf("res ,, %p\n", scene->spheres->next->next);
// 		// printf("next ,, %d\n", scene->planes->next->color.r);
// 		// printf("%p\n", scene->planes->next->next);
// 	}
// 	return (0);
// }
