/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_spotlight.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouarrak <rouarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 06:14:38 by rouarrak          #+#    #+#             */
/*   Updated: 2023/12/11 00:06:52 by rouarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
	free_tab(tab, pos, rgb);
}
