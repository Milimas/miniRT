/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouarrak <rouarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 03:43:36 by rouarrak          #+#    #+#             */
/*   Updated: 2023/12/11 03:55:42 by rouarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void static	fill_pos(char **pos, t_cylinder *l)
{
	check_pos(pos);
	l->position.x = str_to_double(pos[0]);
	l->position.y = str_to_double(pos[1]);
	l->position.z = str_to_double(pos[2]);
}

void static	fill_ort(char **ort, t_cylinder *l)
{
	check_ort(ort);
	l->normal.x = str_to_double(ort[0]);
	l->normal.y = str_to_double(ort[1]);
	l->normal.z = str_to_double(ort[2]);
}

void static	fill_rgb(char **rgb, t_cylinder *l)
{
	check_rgb(rgb);
	l->color.x = (double)ft_atoi(rgb[0]) / 0xFF;
	l->color.y = (double)ft_atoi(rgb[1]) / 0xFF;
	l->color.z = (double)ft_atoi(rgb[2]) / 0xFF;
}

t_cylinder	*cy_new(char	*str, t_object *obj, t_window *win)
{
	t_cylinder	*l;
	char		**tab;
	char		**pos;
	char		**rgb;
	char		**ort;

	l = ft_calloc(sizeof(t_cylinder), 1);
	tab = ft_split(str, ' ');
	check_bfrsplit(tab[1]);
	pos = ft_split(tab[1], ',');
	fill_pos(pos, l);
	check_bfrsplit(tab[2]);
	ort = ft_split(tab[2], ',');
	fill_ort(ort, l);
	l->radius = str_to_double(tab[3]);
	l->height = str_to_double(tab[4]);
	check_bfrsplit(tab[5]);
	rgb = ft_split(tab[5], ',');
	fill_rgb(rgb, l);
	if (tab[6] && ft_strcmp(tab[6], "\n"))
		text_or_chck(tab[6], obj, win);
	free_tab(tab, ort, rgb);
	free_split(pos);
	return (l);
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
	object->local = local_axis(cylinder->normal);
	object->next = NULL;
	append_object(&win->scene.objs, object);
}
