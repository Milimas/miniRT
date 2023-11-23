/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:19:02 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/11/23 13:28:02 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/**
 * @brief Convert a t_trgb color structure to a 32-bit integer color value.
 *
 * This function combines the transparency (t), red (r), green (g), and blue (b)
 * components of a t_trgb color structure to create a 32-bit integer color value.
 *
 * @param color A t_trgb color structure containing transparency, red, green, and
 * blue color components.
 * @return A 32-bit integer color value formed by combining the components of the
 * input t_trgb color structure.
 */
int	trgb_to_int(t_trgb color)
{
	return (color.t << 24 | color.r << 16 | color.g << 8 | color.b);
}

t_trgb	vec_to_rgb(t_color vec)
{
	t_trgb	color;

	color.t = 0;
	color.r = clamp(vec.x * 0xFF, 0, 0xFF);
	color.g = clamp(vec.y * 0xFF, 0, 0xFF);
	color.b = clamp(vec.z * 0xFF, 0, 0xFF);
	return (color);
}

t_color	rgb_to_vec(t_trgb color)
{
	t_color	vec;

	vec.x = (double)color.r / 0xFF;
	vec.y = (double)color.g / 0xFF;
	vec.z = (double)color.b / 0xFF;
	return (vec);
}

t_color	get_color(t_object obj)
{
	if (obj.type == SPHERE)
		return (obj.sphere->color);
	if (obj.type == PLANE)
		return (obj.plane->color);
	if (obj.type == CYLINDER)
		return (obj.cylinder->color);
	if (obj.type == CONE)
		return (obj.cone->color);
	return ((t_color){0xFF, 0x0, 0xFF});
}
