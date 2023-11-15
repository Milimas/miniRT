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

void sphere_map(t_ray *ray)
{
	double theta;
	double phi;

	theta = atan2(ray->hit.normal.x, ray->hit.normal.z) / (2 * M_PI);
	phi = acos(ray->hit.normal.y);

	ray->hit.uv.x = 1 - (theta + .5);
	ray->hit.uv.y = 1 - phi / M_PI;
}