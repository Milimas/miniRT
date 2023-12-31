/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/12/01 19:35:43 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_color	specular(t_ray *ray, t_light light)
{
	t_vector	v;
	t_vector	l;
	t_vector	r;

	if (light.ratio < 0 || light.ratio > 1)
		return ((t_color){0});
	v = norm(v_scale(ray->dir, -1));
	l = norm(v_sub(light.position, ray->hit.at));
	r = norm(v_sub(v_scale(ray->hit.normal, 2 * dot(ray->hit.normal, l)), l));
	return (v_scale(light.color, light.ratio * pow(max(0, dot(r, v)),
				GL_SHINENESS)));
}
