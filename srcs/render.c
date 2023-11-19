
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/23 20:17:53 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	render(t_window *window)
{
	t_pixel		p;
	t_camera	*cam;

	p = (t_pixel){-1, -1};
	cam = window->scene.camera;
	clear_mlx_image(window);
    // t_matrix roty = matrix_rot_y(1);
    // t_matrix rotx = matrix_rot_x(1);
    // t_matrix nroty = matrix_rot_y(-1);
    // window->scene.light->position = dir_matrix(window->scene.light->position, roty);
    // window->scene.camera->position = dir_matrix(window->scene.camera->position, rotx);
    // window->scene.camera->look_at = dir_matrix(window->scene.camera->look_at, rotx);
    // window->scene.camera->position = dir_matrix(window->scene.camera->position, nroty);
    // window->scene.camera->look_at = dir_matrix(window->scene.camera->look_at, nroty);
    // window->scene.camera = create_camera(window->scene.camera);
	while (++p.y < cam->height)
	{
		p.x = -1;
		while (++p.x < cam->width)
		{
			t_ray r = generate_ray(p, cam);
			intersect(&r, window);
			if (r.hit.t != INFINITY)
			{
				r.hit.color = get_color(*r.hit.obj);
				shadow(&r, window);
				put_pixel(&window->img, (t_pixel){p.x, p.y}, trgb_to_int(vec_to_rgb(r.hit.color)));
			}
		}
	}
	mlx_put_image_to_window(window->mlx.mlx_ptr,
		window->mlx.win_ptr, window->img.img_ptr, 0, 0);
	return (0);
}