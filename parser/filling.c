/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimouarrak <rimouarrak@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 06:33:31 by rouarrak          #+#    #+#             */
/*   Updated: 2023/11/28 09:22:46 by rimouarrak       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void static	free_tab(char **tab, char **ort, char **pos)
{
	free_split(tab);
	free_split(pos);
	free_split(ort);
}

void	fill_c(char	*str, t_window *win)
{
	char	**tab;
	char	**pos;
	char	**ort;

	tab = ft_split(str, ' ');
	pos = ft_split(tab[1], ',');
	check_pos(pos);
	win->scene.camera->position.x = str_to_double(pos[0]);
	win->scene.camera->position.y = str_to_double(pos[1]);
	win->scene.camera->position.z = str_to_double(pos[2]);
	ort = ft_split(tab[2], ',');
	check_ort(ort);
	win->scene.camera->dir.x = str_to_double(ort[0]);
	win->scene.camera->dir.y = str_to_double(ort[1]);
	win->scene.camera->dir.z = str_to_double(ort[2]);
	if ((!(ft_atoi(tab[3]) >= 0 && ft_atoi(tab[3]) <= 180))
		|| !ft_isnum(tab[3]))
	{
		printf("Error\nHorizontal field of view in degrees should"
			" be in range [0,180]\n");
		exit(0);
	}
	win->scene.camera->fov = ft_atoi(tab[3]);
	free_tab(tab, ort, pos);
}

void	fill_l(char	*str, t_window *win)
{
	char	**tab;
	char	**pos;
	char	**rgb;

	tab = ft_split(str, ' ');
	pos = ft_split(tab[1], ',');
	check_pos(pos);
	win->scene.light->position.x = str_to_double(pos[0]);
	win->scene.light->position.y = str_to_double(pos[1]);
	win->scene.light->position.z = str_to_double(pos[2]);
	if (!(str_to_double(tab[2]) >= 0 && str_to_double(tab[2]) <= 1))
	{
		printf("Error\nthe light brightness ratio should"
			" be in range [0.0,1.0]\n");
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
	win->scene.ambient->ratio = str_to_double(tab[1]);
	rgb = ft_split(tab[2], ',');
	check_rgb(rgb);
	win->scene.ambient->color.x = (double)ft_atoi(rgb[0]) / 0xFF;
	win->scene.ambient->color.y = (double)ft_atoi(rgb[1]) / 0xFF;
	win->scene.ambient->color.z = (double)ft_atoi(rgb[2]) / 0xFF;
	free_split(tab);
	free_split(rgb);
}
