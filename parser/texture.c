/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimouarrak <rimouarrak@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 06:27:44 by rouarrak          #+#    #+#             */
/*   Updated: 2023/11/28 09:23:36 by rimouarrak       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	set_texture(t_object *obj, t_window *window, char *path)
{
	obj->texture.img_ptr = mlx_xpm_file_to_image(
			window->mlx.mlx_ptr,
			path,
			&obj->texture.width,
			&obj->texture.height
			);
	if (!obj->texture.img_ptr)
	{
		printf("There is something wrong in the xpm file\n");
		exit(0);
	}
	obj->texture.addr = (int *)mlx_get_data_addr(
			obj->texture.img_ptr,
			&obj->texture.bits_per_pixel,
			&obj->texture.size_line,
			&obj->texture.endian);
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
