/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimouarrak <rimouarrak@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/12/11 23:32:58 by rimouarrak       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

void	init_cam(t_camera *cam)
{
	t_vector	up;
	t_pixel		s;

	cam->axis.forward = norm(cam->dir);
	up = norm((t_vector){0, 1, 0});
	cam->axis.right = norm(cross(cam->axis.forward, up));
	if (magnitude(cam->axis.right) == 0)
		cam->axis.right = (t_vector){1, 0, 0};
	cam->axis.up = norm(cross(cam->axis.forward, cam->axis.right));
	s.x = tan((cam->fov * .5 * M_PI / 180));
	s.y = s.x * cam->aspect_ratio;
	cam->u = v_scale(cam->axis.right, (2 * s.x) / (cam->width - 1));
	cam->v = v_scale(cam->axis.up, (2 * s.y) / (cam->height - 1));
	cam->lower_left = v_sub(cam->axis.forward,
			v_add(v_scale(cam->axis.right, s.x), v_scale(cam->axis.up, s.y)));
}

t_camera	*create_camera(t_camera *cam)
{
	cam->width = WIN_WIDTH;
	cam->height = WIN_HEIGHT;
	cam->aspect_ratio = (cam->height - 1) / (cam->width - 1);
	init_cam(cam);
	return (cam);
}

int	key_down(int keycode, t_window *window)
{
	if (keycode == K_ESCAPE)
		close_window(&window->mlx);
	return (0);
}

void	ray_tracing(t_window *window)
{
	window->scene.camera = create_camera(window->scene.camera);
	render(window);
	mlx_key_hook(window->mlx.win_ptr, key_down, window);
	mlx_hook(window->mlx.win_ptr, 17, 0, close_window, &window->mlx);
	mlx_loop(window->mlx.mlx_ptr);
}

int	main(int ac, char **av)
{
	char		**file_tab;
	t_window	window;

	window.scene.objs = NULL;
	window.scene.spots = NULL;
	if (ac == 2)
	{
		check_rt(av[1]);
		file_tab = read_file(av[1]);
		if (!file_tab)
		{
			printf("Error\nThe .rt file is empty or unexisting\n");
			return (0);
		}
		init_window(&window);
		supervisor(file_tab);
		init_struct(&window.scene);
		fill_elm(file_tab, &window);
		free_split(file_tab);
		ray_tracing(&window);
	}
	return (0);
}
