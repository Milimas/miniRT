
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

#include "../../includes/minirt.h"

void	print_vector(char *str, t_vector v)
{
	printf("%s: (%f, %f, %f)\n", str, v.x, v.y, v.z);
}

void print_scene(t_window window)
{
	t_camera cam = *window.scene.camera;
	printf("camera:\n");
	print_vector("position", cam.position);
	print_vector("look_at", cam.look_at);
	printf("fov: %f\n\n", cam.fov);
	t_object *it = window.scene.objs;
	while (it)
	{
		if (it->type == CYLINDER)
		{
			t_cylinder c = *(t_cylinder*)it->cylinder;
			printf("cylinder:\n");
			print_vector("position", c.position);
			print_vector("axis", c.normal);
			printf("radius %f\n", c.radius);
			print_vector("color", c.color);
		}
		if (it->type == PLANE)
		{
			t_plane c = *(t_plane*)it->plane;
			printf("plane:\n");
			print_vector("position", c.position);
			print_vector("axis", c.normal);
			print_vector("color", c.color);
		}
		if (it->type == SPHERE)
		{
			t_sphere c = *(t_sphere*)it->sphere;
			printf("sphere:\n");
			print_vector("position", c.position);
			printf("radius %f\n", c.radius);
			print_vector("color", c.color);
		}
		it = it->next;
	}
}