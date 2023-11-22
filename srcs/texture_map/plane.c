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

void	plane_map(t_ray *ray)
{
	// check for y != 1
	 
// Vector3 v = pointOnPlane - origin;
// Vector2 positionInPlane = new Vector2(Vector3.Dot(planeXDir, v), Vector3.Dot(planeYDir, v));
	// t_plane plane = *ray->hit.obj->plane;
	t_vector	v = v_sub(ray->hit.at, ray->hit.obj->plane->position);

	t_pixel		uv;
	uv.x = dot(ray->hit.obj->local.right, v);
	uv.y = dot(ray->hit.obj->local.forward, v);
	ray->hit.uv.x = fmod(uv.x, 1);
	ray->hit.uv.y = fmod(uv.y, 1);
}