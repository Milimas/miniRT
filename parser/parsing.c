/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouarrak <rouarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:38:57 by rimouarrak        #+#    #+#             */
/*   Updated: 2023/11/20 21:20:22 by rouarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void    check_rgb(char **rgb)
{
    double    r;
    double    g;
    double    b;

    if (!((rgb[0] && rgb[1] && rgb[2]) && rgb[2][0] != '\n' && !rgb[3]))
    {
        printf("Error\nSomething is wrong in RGB parameter\n");
        exit (0);
    }
    r = (double)ft_atoi(rgb[0]) / 0xFF;
    g = (double)ft_atoi(rgb[1]) / 0xFF;
    b = (double)ft_atoi(rgb[2]) / 0xFF;
    if (! (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255))
    {
        printf("Error\nThe RGB values should be between 0 and 255\n");
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

void	fill_a(char	*str, t_window *win)
{
	char	**tab;
	char	**rgb;

	tab = ft_split(str, ' ');
	if (!(str_to_double(tab[1]) >= 0 && str_to_double(tab[1]) <= 1))
	{
		printf("Error\nAmbient lighting ratio should be in range [0.0,1.0]\n");
		exit(0);
	}
	win->scene.ambient->ratio =str_to_double(tab[1]);
	rgb = ft_split(tab[2], ',');
	check_rgb(rgb);
	win->scene.ambient->color.x = (double)ft_atoi(rgb[0]) / 0xFF;
	win->scene.ambient->color.y = (double)ft_atoi(rgb[1]) / 0xFF;
	win->scene.ambient->color.z = (double)ft_atoi(rgb[2]) / 0xFF;
	free_split(tab);
	free_split(rgb);
}

void	check_ort(char **ort)
{
	double x;
	double y;
	double z;

	x = str_to_double(ort[0]);
	y = str_to_double(ort[1]);
	z = str_to_double(ort[2]);
	if (! (x >= -1 && x <= 1 && y >= -1 && y <= 1 && z >= -1 && z <= 1))
	{
		printf("Error\nThe 3d normalized orientation vector should be in range [-1,1] for each x,y,z axis\n");
		exit (0);
	}
}

void	fill_c(char	*str, t_window *win)
{
	char	**tab;
	char	**pos;
	char	**ort;

	tab = ft_split(str, ' ');
	pos = ft_split(tab[1], ',');
	win->scene.camera->position.x = str_to_double(pos[0]);
	win->scene.camera->position.y = str_to_double(pos[1]);
	win->scene.camera->position.z = str_to_double(pos[2]);
	ort = ft_split(tab[2], ',');
	check_ort(ort);
	win->scene.camera->look_at.x = str_to_double(ort[0]);
	win->scene.camera->look_at.y = str_to_double(ort[1]);
	win->scene.camera->look_at.z = str_to_double(ort[2]);
	if (!(ft_atoi(tab[3]) >= 0 && ft_atoi(tab[3]) <= 180))
	{
		printf("Error\nHorizontal field of view in degrees should be in range [0,180]\n");
		exit(0);
	}
	win->scene.camera->fov = ft_atoi(tab[3]);
	free_split(tab);
	free_split(pos);
	free_split(ort);
}

void	fill_l(char	*str, t_window *win)
{
	char	**tab;
	char	**pos;
	char	**rgb;

	tab = ft_split(str, ' ');
	pos = ft_split(tab[1], ',');
	win->scene.light->position.x = str_to_double(pos[0]);
	win->scene.light->position.y = str_to_double(pos[1]);
	win->scene.light->position.z = str_to_double(pos[2]);
	if (!(str_to_double(tab[2]) >= 0 && str_to_double(tab[2]) <= 1))
	{
		printf("Error\nthe light brightness ratio should be in range [0.0,1.0]\n");
		exit(0);
	}
	win->scene.light->ratio = str_to_double(tab[2]);
	rgb = ft_split(tab[3], ',');
	check_rgb(rgb);
	win->scene.light->color.x = (double)ft_atoi(rgb[0]) / 0xFF;
	win->scene.light->color.y = (double)ft_atoi(rgb[1]) / 0xFF;
	win->scene.light->color.z = (double)ft_atoi(rgb[2]) / 0xFF;
	free_split(tab);
	free_split(rgb);
	free_split(pos);
}

void	fill_sl(char	*str, t_window *win)
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
	if (tab[4] && ft_strcmp(tab[4] , "\n"))
		text_or_chck(tab[4], object, win);
	append_object(&win->scene.spots, object);
	free_split(tab);
	free_split(rgb);
	free_split(pos);
}

void	fill_pl(char	*str, t_window *win)
{
	t_plane		*plane;
	t_object	*object;

	object = ft_calloc(sizeof(t_object), 1);
	plane = pl_new(str, object, win);
	plane->normal = norm(plane->normal);
	object->plane = plane;
	object->type = PLANE;
	object->next = NULL;
	object->local = local_axis(plane->normal);
	append_object(&win->scene.objs, object);
}

void	fill_sp(char	*str, t_window *win)
{
	t_sphere	*sphere;
	t_object	*object;

	object = ft_calloc(sizeof(t_object), 1);
	sphere = sp_new(str, object, win);
	object->sphere = sphere;
	object->type = SPHERE;
	object->next = NULL;
	append_object(&win->scene.objs, object);
}

void	fill_cy(char	*str, t_window *win)
{
	t_cylinder	*cylinder;
	t_object	*object;

	object = ft_calloc(sizeof(t_object), 1);
	cylinder = cy_new(str, object, win);
	cylinder->normal = norm(cylinder->normal);
	object->cylinder = cylinder;
	object->type = CYLINDER;
	object->next = NULL;
	append_object(&win->scene.objs, object);
}

void	fill_cn(char	*str, t_window *win)
{
	t_cone		*cone;
	t_object	*object;

	object = ft_calloc(sizeof(t_object), 1);
	cone = cn_new(str, object, win);
	cone->normal = norm(cone->normal);
	object->cone = cone;
	object->type = CONE;
	object->next = NULL;
	append_object(&win->scene.objs, object);
}

void	fill_elm(char	**tab, t_window *win)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], "A", 1))
			fill_a(tab[i], win);
		else if (!ft_strncmp(tab[i], "C", 1))
			fill_c(tab[i], win);
		else if (!ft_strncmp(tab[i], "L", 1))
			fill_l(tab[i], win);
		else if (!ft_strncmp(tab[i], "pl", 2))
			fill_pl(tab[i], win);
		else if (!ft_strncmp(tab[i], "sp", 2))
			fill_sp(tab[i], win);
		else if (!ft_strncmp(tab[i], "cy", 2))
			fill_cy(tab[i], win);
		else if (!ft_strncmp(tab[i], "cn", 2))
			fill_cn(tab[i], win);
		else if (!ft_strncmp(tab[i], "sl", 2))
			fill_sl(tab[i],win);
		i++;
	}
}

void	init_struct(t_scene *scene)
{
	scene->ambient = ft_calloc(1, sizeof(t_ambient_light));
	scene->camera = ft_calloc(1, sizeof(t_camera));
	scene->light = ft_calloc(1, sizeof(t_light));
}
