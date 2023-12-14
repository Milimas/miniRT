/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:08:22 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/11/23 15:08:20 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_color	apply_light(t_color surface, t_color light)
{
	t_color	res;

	res.x = clamp(surface.x * light.x, 0, 1);
	res.y = clamp(surface.y * light.y, 0, 1);
	res.z = clamp(surface.z * light.z, 0, 1);
	return (res);
}
