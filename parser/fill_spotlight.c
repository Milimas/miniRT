/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_spotlight.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimouarrak <rimouarrak@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 06:14:38 by rouarrak          #+#    #+#             */
/*   Updated: 2023/12/10 23:39:15 by rimouarrak       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// t_spots	*sl_new(char	*str )
// {
// 	t_spots	*l;
// 	char	**tab;
// 	char	**pos;
// 	char	**rgb;
// 	char	**ort;

// 	l = malloc (sizeof(t_spots));
// 	if (!l)
// 		return (NULL);
// 	tab = ft_split(str, ' ');
// 	pos = ft_split(tab[1], ',');
//	check_pos(pos);
// 	l->position.x = str_to_double(pos[0]);
// 	l->position.y = str_to_double(pos[1]);
// 	l->position.z = str_to_double(pos[2]);
// 	ort = ft_split(tab[2], ',');
//	check_ort(ort);
// 	l->direction.x = str_to_double(ort[0]);
// 	l->direction.y = str_to_double(ort[1]);
// 	l->direction.z = str_to_double(ort[2]);
// 	l->ratio = str_to_double(tab[3]);
// 	rgb = ft_split(tab[4], ',');
// 	l->color.x = (double)ft_atoi(rgb[0]) / 0xFF;
// 	l->color.y = (double)ft_atoi(rgb[1]) / 0xFF;
// 	l->color.z = (double)ft_atoi(rgb[2]) / 0xFF;
// 	// l -> next = NULL;
// 	free_split(tab);
// 	free_split(ort);
// 	free_split(rgb);
// 	free_split(pos);
// 	return (l);
// }

void	fill_sl(char	*str, t_window *win)
{
	char		**tab;
	char		**pos;
	char		**rgb;
	t_object	*object;
	t_light		*light;

	tab = ft_split(str, ' ');
	check_bfrsplit(tab[1]);
	pos = ft_split(tab[1], ',');
	check_pos(pos);
	object = ft_calloc(sizeof(t_object), 1);
	light = ft_calloc(sizeof(t_light), 1);
	light->position.x = str_to_double(pos[0]);
	light->position.y = str_to_double(pos[1]);
	light->position.z = str_to_double(pos[2]);
	light->ratio = str_to_double(tab[2]);
	check_bfrsplit(tab[3]);
	rgb = ft_split(tab[3], ',');
	check_rgb(rgb);
	light->color.x = (double)ft_atoi(rgb[0]) / 0xFF;
	light->color.y = (double)ft_atoi(rgb[1]) / 0xFF;
	light->color.z = (double)ft_atoi(rgb[2]) / 0xFF;
	object->spot = light;
	append_object(&win->scene.spots, object);
	free_split(tab);
	free_split(rgb);
	free_split(pos);
}
