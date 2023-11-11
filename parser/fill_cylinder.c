/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimouarrak <rimouarrak@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 03:43:36 by rimouarrak        #+#    #+#             */
/*   Updated: 2023/09/10 19:38:47 by rimouarrak       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

// t_cylinder	*cy_last(t_cylinder *lst)
// {
// 	t_cylinder	*l;

// 	if (!lst)
// 		return (NULL);
// 	l = lst;
// 	while (l -> next != NULL)
// 	{
// 		l = l -> next;
// 	}
// 	return (l);
// }

t_cylinder	*cy_new(char	*str)
{
	t_cylinder	*l;
	char		**tab;
	char		**pos;
	char		**rgb;
	char		**ort;

	l = malloc (sizeof(t_cylinder));
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
	l->radius = str_to_double(tab[3]);
	l->height = str_to_double(tab[4]);
	rgb = ft_split(tab[5], ',');
	l->color.x = (double)ft_atoi(rgb[0]) / 0xFF;
	l->color.y = (double)ft_atoi(rgb[1]) / 0xFF;
	l->color.z = (double)ft_atoi(rgb[2]) / 0xFF;
	// l -> next = NULL;
	free_split(tab);
	free_split(ort);
	free_split(rgb);
	free_split(pos);
	return (l);
}

// void	cy_add_back(t_cylinder **lst, t_cylinder *new)
// {
// 	t_cylinder	*l;

// 	if (!*lst)
// 		*lst = new;
// 	else
// 	{
// 		l = cy_last(*lst);
// 		// l -> next = new;
// 	}
// }
