/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/11/23 15:35:56 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	print_vector(char *str, t_vector v)
{
	printf("%s: (%f, %f, %f)\n", str, v.x, v.y, v.z);
}

void	print_scene(t_window window)
{
	t_object	*it;

	it = window.scene.objs;
	print_camera(window.scene.camera);
	while (it)
	{
		if (it->type == CYLINDER)
			print_cylinder(it->cylinder);
		if (it->type == PLANE)
			print_plane(it->plane);
		if (it->type == SPHERE)
			print_sphere(it->sphere);
		it = it->next;
	}
}
