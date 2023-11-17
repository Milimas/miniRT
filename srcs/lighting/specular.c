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

t_color	specular(t_ray *ray, t_light light)
{
	if (light.ratio < 0 || light.ratio > 1)
		return ((t_color){0});
	t_vector v = norm(v_scale(ray->dir, -1));
	t_vector l = norm(v_sub(light.position, ray->hit.at));
	t_vector r = norm(v_sub(v_scale(ray->hit.normal, 2 * dot(ray->hit.normal, l)), l));
	// t_vector h = norm(v_add(v, l));
	// t_vector n = ray->hit.normal;
	// double nl = dot(n, l);
	// if (nl < 0)
	// 	return ((t_color){0});
	// return (v_scale(light.color, light.ratio * pow(max(0, dot(ray->hit.normal, h)), 64)));
	return (v_scale(light.color, light.ratio * pow(max(0, dot(r, v)), 64)));
}