/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/11/23 15:17:51 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	sphere_map(t_ray *ray)
{
	double	theta;
	double	phi;

	theta = atan2(ray->hit.normal.x, ray->hit.normal.z) / (2 * M_PI);
	phi = acos(ray->hit.normal.y);
	ray->hit.uv.x = (theta + .5);
	ray->hit.uv.y = phi / M_PI;
}
