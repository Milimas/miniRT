/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/11/23 15:17:24 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	plane_map(t_ray *ray)
{
	t_vector	v;
	t_pixel		uv;

	v = v_sub(ray->hit.at, ray->hit.obj->plane->position);
	uv.x = dot(ray->hit.obj->local.right, v);
	uv.y = dot(ray->hit.obj->local.forward, v);
	ray->hit.uv.x = fmod(uv.x, 1);
	ray->hit.uv.y = fmod(uv.y, 1);
}
