/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/19 22:01:35 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include <stdio.h>

int	render(t_window *window)
{
	put_pixel(&window->img, 0, 0, 0x00ffffff);
	mlx_put_image_to_window(window->mlx->mlx_ptr, window->mlx->win_ptr, window->img.img_ptr, 0, 0);
	return (0);
}

int	main( void )
{
	t_window	window;
	t_mlx		mlx;

	window.mlx = &mlx;
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	window.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	window.img.addr = mlx_get_data_addr(
			window.img.img_ptr,
			&window.img.bits_per_pixel,
			&window.img.size_line,
			&window.img.endian);
	mlx_loop_hook(mlx.mlx_ptr, render, &window);
	mlx_loop(mlx.mlx_ptr);
}
