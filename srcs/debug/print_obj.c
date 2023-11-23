/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:36:16 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/11/23 16:55:17 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	print_cylinder(t_cylinder *c)
{
	printf("cylinder:\n");
	print_vector("position", c->position);
	print_vector("axis", c->normal);
	printf("radius %f\n", c->radius);
	print_vector("color", c->color);
}

void	print_camera(t_camera *cam)
{
	printf("camera:\n");
	print_vector("position", cam->position);
	print_vector("dir", cam->dir);
	printf("fov: %f\n\n", cam->fov);
}

void	print_plane(t_plane *p)
{
	printf("plane:\n");
	print_vector("position", p->position);
	print_vector("axis", p->normal);
	print_vector("color", p->color);
}

void	print_sphere(t_sphere *s)
{
	printf("sphere:\n");
	print_vector("position", s->position);
	printf("radius %f\n", s->radius);
	print_vector("color", s->color);
}
