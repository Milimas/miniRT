/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 03:31:28 by rimouarrak        #+#    #+#             */
/*   Updated: 2023/11/23 17:54:55 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// t_sphere	*sp_last(t_sphere *lst)
// {
// 	t_sphere	*l;

// 	if (!lst)
// 		return (NULL);
// 	l = lst;
// 	while (l -> next != NULL)
// 	{
// 		l = l -> next;
// 	}
// 	return (l);
// }

// void	fill_texture()
// {

// }

 //make a new strstrim for the next function

void text_or_chck(char *str, t_object	*obj, t_window *win)
{
	if (ft_strcmp(str, "checker") == 0 || ft_strcmp(str, "checker\n") == 0)
		obj->checkerboard = 1;
	else
	{
		obj->checkerboard = 0;
	// 	obj->texture.img_ptr = mlx_xpm_file_to_image(win->mlx.mlx_ptr, "textures/03_Topo_small.xpm",
	// &obj->texture.width,
	// &obj->texture.height);
	// if (!obj->texture.img_ptr)
	// {
	// 	printf("Error\nSomething is wrong with the texture you provided\n");
	// 	exit(0);
	// }
	// 	obj->texture.addr = (int *)mlx_get_data_addr(
	// 	obj->texture.img_ptr,
	// 	&obj->texture.bits_per_pixel,
	// 	&obj->texture.size_line,
	// 	&obj->texture.endian
	// );
	(void)win;
	}
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
	pos = ft_split(tab[1], ',');
	l->position.x = str_to_double(pos[0]);
	l->position.y = str_to_double(pos[1]);
	l->position.z = str_to_double(pos[2]);
	l->radius = str_to_double(tab[2]) / 2;
	rgb = ft_split(tab[3], ',');
	check_rgb(rgb);
	l->color.x = (double)ft_atoi(rgb[0]) / 0xFF;
	l->color.y = (double)ft_atoi(rgb[1]) / 0xFF;
	l->color.z = (double)ft_atoi(rgb[2]) / 0xFF;
	if (tab[4] && ft_strcmp(tab[4] , "\n"))
		text_or_chck(tab[4], object, win);
	set_texture(object, win, "textures/03_Topo_small.xpm");
	// l -> next = NULL;
	free_split(tab);
	free_split(rgb);
	free_split(pos);
	return (l);
}

// void	sp_add_back(t_sphere **lst, t_sphere *new)
// {
// 	t_sphere	*l;

// 	if (!*lst)
// 		*lst = new;
// 	else
// 	{
// 		l = sp_last(*lst);
// 		l -> next = new;
// 	}
// }
