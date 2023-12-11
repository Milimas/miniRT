/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimouarrak <rimouarrak@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 01:19:20 by rimouarrak        #+#    #+#             */
/*   Updated: 2023/12/11 00:06:00 by rimouarrak       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void static	fill_pos(char **pos, t_plane *l)
{
	check_pos(pos);
	l->position.x = str_to_double(pos[0]);
	l->position.y = str_to_double(pos[1]);
	l->position.z = str_to_double(pos[2]);
}

void static	fill_ort(char **ort, t_plane *l)
{
	check_ort(ort);
	l->normal.x = str_to_double(ort[0]);
	l->normal.y = str_to_double(ort[1]);
	l->normal.z = str_to_double(ort[2]);
}

void static	fill_rgb(char **rgb, t_plane *l)
{
	check_rgb(rgb);
	l->color.x = (double)ft_atoi(rgb[0]) / 0xFF;
	l->color.y = (double)ft_atoi(rgb[1]) / 0xFF;
	l->color.z = (double)ft_atoi(rgb[2]) / 0xFF;
}

t_plane	*pl_new(char	*str, t_object *obj, t_window *win)
{
	t_plane	*l;
	char	**tab;
	char	**pos;
	char	**rgb;
	char	**ort;

	l = ft_calloc(sizeof(t_plane), 1);
	if (!l)
		return (NULL);
	tab = ft_split(str, ' ');
	check_bfrsplit(tab[1]);
	pos = ft_split(tab[1], ',');
	fill_pos(pos, l);
	check_bfrsplit(tab[2]);
	ort = ft_split(tab[2], ',');
	fill_ort(ort, l);
	check_bfrsplit(tab[3]);
	rgb = ft_split(tab[3], ',');
	fill_rgb(rgb, l);
	if (tab[4] && ft_strcmp(tab[4], "\n"))
		text_or_chck(tab[4], obj, win);
	free_tab(tab, ort, rgb);
	free_split(pos);
	return (l);
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
