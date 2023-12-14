/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouarrak <rouarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/11/23 19:07:29 by rouarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	render(t_window *window)
{
	t_pixel		p;
	t_camera	*cam;
	t_ray		r;

	p = (t_pixel){-1, -1};
	cam = window->scene.camera;
	clear_mlx_image(window);
	while (++p.y < cam->height)
	{
		p.x = -1;
		while (++p.x < cam->width)
		{
			r = generate_ray(p, cam);
			intersect(&r, window);
			if (r.hit.t != INFINITY)
			{
				shadow(&r, window);
				put_pixel(&window->img, (t_pixel){p.x, p.y},
					trgb_to_int(vec_to_rgb(r.hit.color)));
			}
		}
	}
	mlx_put_image_to_window(window->mlx.mlx_ptr,
		window->mlx.win_ptr, window->img.img_ptr, 0, 0);
	return (0);
}
