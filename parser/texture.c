/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 06:27:44 by rouarrak          #+#    #+#             */
/*   Updated: 2023/11/30 13:18:20 by rouarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	set_texture(t_object *obj, t_window *window, char *path)
{
	obj->height_map.img_ptr = mlx_xpm_file_to_image(
			window->mlx.mlx_ptr,
			path,
			&obj->height_map.width,
			&obj->height_map.height
			);
	if (!obj->height_map.img_ptr)
	{
		printf("There is something wrong in the xpm file\n");
		exit(0);
	}
	obj->height_map.addr = (int *)mlx_get_data_addr(
			obj->height_map.img_ptr,
			&obj->height_map.bits_per_pixel,
			&obj->height_map.size_line,
			&obj->height_map.endian);
}

char	*rm_n(char *str)
{
	int		size;
	char	*res;

	size = ft_strlen(str);
	if (str[size - 1] == '\n')
	{
		res = malloc(size);
		ft_strlcpy(res, str, size);
		return (res);
	}
	return (NULL);
}

void	text_or_chck(char *str, t_object	*obj, t_window *win)
{
	char	*path;

	if (ft_strcmp(str, "checker") == 0 || ft_strcmp(str, "checker\n") == 0)
		obj->checkerboard = 1;
	else
	{
		obj->checkerboard = 0;
		path = rm_n(str);
		if (!path)
			set_texture(obj, win, str);
		else
			set_texture(obj, win, path);
		free(path);
	}
}
