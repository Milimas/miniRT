/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/11/23 15:08:15 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_color	diffuse(t_ray *ray, t_light light)
{
	t_vector	l;
	t_vector	n;
	double		nl;

	if (light.ratio < 0 || light.ratio > 1)
		return ((t_color){0});
	l = norm(v_sub(light.position, ray->hit.at));
	n = ray->hit.normal;
	nl = dot(n, l);
	if (nl < 0)
		return ((t_color){0});
	return (v_scale(light.color, max(0, nl) * light.ratio));
}
