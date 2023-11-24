/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 03:43:36 by rimouarrak        #+#    #+#             */
/*   Updated: 2023/11/24 19:02:56 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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

t_cylinder	*cy_new(char	*str, t_object *obj, t_window *win)
{
	t_cylinder	*l;
	char		**tab;
	char		**pos;
	char		**rgb;
	char		**ort;

	l = ft_calloc(sizeof(t_cylinder), 1);
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
	check_rgb(rgb);
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
