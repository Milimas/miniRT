/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouarrak <rouarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 03:31:28 by rouarrak          #+#    #+#             */
/*   Updated: 2023/12/10 23:39:09 by rouarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void static	fill_pos(char **pos, t_sphere *l)
{
	check_pos(pos);
	l->position.x = str_to_double(pos[0]);
	l->position.y = str_to_double(pos[1]);
	l->position.z = str_to_double(pos[2]);
}

void static	fill_rgb(char **rgb, t_sphere *l)
{
	check_rgb(rgb);
	l->color.x = (double)ft_atoi(rgb[0]) / 0xFF;
	l->color.y = (double)ft_atoi(rgb[1]) / 0xFF;
	l->color.z = (double)ft_atoi(rgb[2]) / 0xFF;
}

t_sphere	*sp_new(char	*str, t_object	*object, t_window *win)
{
	t_sphere	*l;
	char		**tab;
	char		**pos;
	char		**rgb;

	l = ft_calloc(sizeof(t_sphere), 1);
	if (!l)
		return (NULL);
	tab = ft_split(str, ' ');
	check_bfrsplit(tab[1]);
	pos = ft_split(tab[1], ',');
	fill_pos(pos, l);
	l->radius = str_to_double(tab[2]) / 2;
	check_bfrsplit(tab[3]);
	rgb = ft_split(tab[3], ',');
	fill_rgb(rgb, l);
	if (tab[4] && ft_strcmp(tab[4], "\n"))
		text_or_chck(tab[4], object, win);
	free_split(tab);
	free_split(rgb);
	free_split(pos);
	return (l);
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
