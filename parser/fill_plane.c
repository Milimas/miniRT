/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 01:19:20 by rimouarrak        #+#    #+#             */
/*   Updated: 2023/11/23 17:08:48 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// t_plane	*pl_last(t_plane *lst)
// {
// 	t_plane	*l;

// 	if (!lst)
// 		return (NULL);
// 	l = lst;
// 	while (l -> next != NULL)
// 	{
// 		l = l -> next;
// 	}
// 	return (l);
// }

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
	pos = ft_split(tab[1], ',');
	l->position.x = str_to_double(pos[0]);
	l->position.y = str_to_double(pos[1]);
	l->position.z = str_to_double(pos[2]);
	ort = ft_split(tab[2], ',');
	l->normal.x = str_to_double(ort[0]);
	l->normal.y = str_to_double(ort[1]);
	l->normal.z = str_to_double(ort[2]);
	rgb = ft_split(tab[3], ',');
	check_rgb(rgb);
	l->color.x = (double)ft_atoi(rgb[0]) / 0xFF;
	l->color.y = (double)ft_atoi(rgb[1]) / 0xFF;
	l->color.z = (double)ft_atoi(rgb[2]) / 0xFF;
	if (tab[4] && ft_strcmp(tab[4] , "\n"))
		text_or_chck(tab[4], obj, win);
	// l -> next = NULL;
	free_split(tab);
	free_split(ort);
	free_split(rgb);
	free_split(pos);
	return (l);
}

t_spots	*sl_new(char	*str )
{
	t_spots	*l;
	char	**tab;
	char	**pos;
	char	**rgb;
	char	**ort;

	l = malloc (sizeof(t_spots));
	if (!l)
		return (NULL);

	tab = ft_split(str, ' ');
	pos = ft_split(tab[1], ',');
	l->position.x = str_to_double(pos[0]);
	l->position.y = str_to_double(pos[1]);
	l->position.z = str_to_double(pos[2]);
	ort = ft_split(tab[2], ',');
	l->direction.x = str_to_double(ort[0]);
	l->direction.y = str_to_double(ort[1]);
	l->direction.z = str_to_double(ort[2]);
	l->ratio = str_to_double(tab[3]);
	rgb = ft_split(tab[4], ',');
	l->color.x = (double)ft_atoi(rgb[0]) / 0xFF;
	l->color.y = (double)ft_atoi(rgb[1]) / 0xFF;
	l->color.z = (double)ft_atoi(rgb[2]) / 0xFF;
			printf("ICI\n");
	printf("spot =============== %d\n", ft_atoi(rgb[2]));
	// l -> next = NULL;
	free_split(tab);
	free_split(ort);
	free_split(rgb);
	free_split(pos);
	return (l);
}

// void	pl_add_back(t_plane **lst, t_plane *new)
// {
// 	t_plane	*l;

// 	if (!*lst)
// 		*lst = new;
// 	else
// 	{
// 		l = pl_last(*lst);
// 		l -> next = new;
// 	}
// }
