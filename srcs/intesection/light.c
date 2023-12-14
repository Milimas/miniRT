/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/11/23 14:17:41 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	light_int(t_ray *ray, t_light *light)
{
	double		t;
	t_vector	oc;
	t_light		*l;

	l = light;
	oc = v_sub(l->position, ray->origin);
	t = magnitude(oc);
	if (t > ELIPS && t < ray->hit.t)
	{
		ray->hit.t = t;
		ray->hit.at = at(*ray, t);
		ray->hit.obj = NULL;
		ray->hit.type = POINT_LIGHT;
		return (t);
	}
	return (0);
}
