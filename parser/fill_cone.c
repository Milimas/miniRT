/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouarrak <rouarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 06:12:53 by rouarrak          #+#    #+#             */
/*   Updated: 2023/11/24 06:13:27 by rouarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_cone	*cn_new(char	*str, t_object *obj, t_window *win)
{
	t_cone		*l;
	char		**tab;
	char		**pos;
	char		**rgb;
	char		**ort;

	l = ft_calloc(sizeof(t_cone), 1);
	if (!l)
		return (NULL);
	tab = ft_split(str, ' ');
	pos = ft_split(tab[1], ',');
	l->position.x = str_to_double(pos[0]);
	l->position.y = str_to_double(pos[1]);
	l->position.z = str_to_double(pos[2]);
	ort = ft_split(tab[2], ',');
	l->normal.x = str_to_double(ort[0]);
	l->normal.y = str_to_double(ort[1]);
	l->normal.z = str_to_double(ort[2]);
	l->angle = str_to_double(tab[3]);
	l->height = str_to_double(tab[4]);
	rgb = ft_split(tab[5], ',');
	l->color.x = (double)ft_atoi(rgb[0]) / 0xFF;
	l->color.y = (double)ft_atoi(rgb[1]) / 0xFF;
	l->color.z = (double)ft_atoi(rgb[2]) / 0xFF;
	if (tab[6] && ft_strcmp(tab[6], "\n"))
		text_or_chck(tab[6], obj, win);
	// l -> next = NULL;
	free_split(tab);
	free_split(ort);
	free_split(rgb);
	free_split(pos);
	return (l);
}
