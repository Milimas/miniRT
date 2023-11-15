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
	t_vector v = normalize_vector(vector_scale(ray->dir, -1));
	t_vector l = normalize_vector(vector_subtraction(light.position, ray->hit.at));
	t_vector r = normalize_vector(vector_subtraction(vector_scale(ray->hit.normal, 2 * dot_product(ray->hit.normal, l)), l));
	// t_vector n = ray->hit.normal;
	// double nl = dot_product(n, l);
	// if (nl < 0)
	// 	return ((t_color){0});
	return (vector_scale(light.color, light.ratio * pow(max(0, dot_product(r, v)), 32)));
}