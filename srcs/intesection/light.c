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

double	light_int(t_ray *ray, t_light *light)
{
	double		t;
	t_vector	oc;
	t_light		*l;

	l = light;
	oc = vector_subtraction(l->position, ray->origin);
	t = vector_magnitude(oc);
	if (t > ELIPS && t < ray->hit.t)
	{
		ray->hit.t = t;
		ray->hit.at = at(*ray, t);
		ray->hit.type = POINT_LIGHT;
		return (t);
	}
	return (0);
}