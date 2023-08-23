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

#include "includes/minirt.h"

#define FRAME_PER_SECOND 60
#define SEC_TO_USEC_MULTIPLIER 1000000

int	generate_color(t_pixel p, int frame)
{
	double	time;
	t_trgb	color;

	time = (double)frame / 1000;
	color.t = 0x0;
	color.r = (int)(127.0 + 127.0 * sin((time + p.x) / WIN_HEIGHT));
	color.g = (int)(127.0 + 127.0 * sin((time + p.y) / WIN_HEIGHT));
	color.b = (int)(127.0 + 127.0 * sin((time + p.x + p.y) / WIN_HEIGHT));
	return (trgb_to_int(color));
}

int	render(t_window *window)
{
	static t_pixel		origin = (t_pixel){0, 0};
	static t_pixel		size = (t_pixel){100, 100};
	static unsigned int	frame = 0;
	t_pixel				cursor;
	static t_pixel		vec = (t_pixel){-1, -1};
	char				*frame_str;

	clear_mlx_image(window);
	cursor.x = origin.x;
	while (cursor.x < origin.x + size.x)
	{
		cursor.y = origin.y;
		while (cursor.y < origin.y + size.y)
		{
			put_pixel(&window->img, cursor, generate_color(origin, frame));
			cursor.y++;
		}
		cursor.x++;
	}
	if (origin.x + size.x >= WIN_WIDTH || origin.x < 0)
		vec.x *= -1;
	if (origin.y + size.y >= WIN_HEIGHT || origin.y < 0)
		vec.y *= -1;
	origin.x += vec.x;
	origin.y += vec.y;
	mlx_put_image_to_window(window->mlx.mlx_ptr,
		window->mlx.win_ptr, window->img.img_ptr, 0, 0);
	frame_str = ft_itoa(frame);
	mlx_string_put(window->mlx.mlx_ptr, window->mlx.win_ptr, 10, 10, 0x00FFFFFF, frame_str);
	free(frame_str);
	usleep((1.0f / FRAME_PER_SECOND) * SEC_TO_USEC_MULTIPLIER);
	frame++;
	return (0);
}

void	init_window(t_window *window)
{
	ft_bzero(&window->scene, sizeof(t_scene));
	window->mlx.mlx_ptr = mlx_init();
	window->mlx.win_ptr = mlx_new_window(window->mlx.mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	window->img.img_ptr = mlx_new_image(window->mlx.mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT);
	window->img.addr = (int *)mlx_get_data_addr(
			window->img.img_ptr,
			&window->img.bits_per_pixel,
			&window->img.size_line,
			&window->img.endian);
}

int	main( void )
{
	t_window	window;

	init_window(&window);
	mlx_loop_hook(window.mlx.mlx_ptr, render, &window);
	mlx_loop(window.mlx.mlx_ptr);
}
