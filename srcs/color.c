/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:19:02 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/23 20:02:55 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/*
 * Create a 32-bit TRGB color value.
 *
 * This function combines the transparency (t), red (r), green (g), and blue (b)
 * components to create a 32-bit TRGB color value.
 *
 * Parameters:
 * - t: The transparency component (0-255).
 * - r: The red component (0-255).
 * - g: The green component (0-255).
 * - b: The blue component (0-255).
 *
 * Returns:
 * A 32-bit TRGB color value formed by combining the provided components.
 */
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/*
 * Convert a t_trgb color structure to a 32-bit integer color value.
 *
 * This function combines the transparency (t), red (r), green (g), and blue (b)
 * components of a t_trgb color structure to create a 32-bit integer color value.
 *
 * Parameters:
 * - color: A t_trgb color structure containing transparency, red, green, and
 * blue color components.
 *
 * Returns:
 * A 32-bit integer color value formed by combining the components of the input
 * t_trgb color structure.
 */
int	trgb_to_int(t_trgb color)
{
	return (color.t << 24 | color.r << 16 | color.g << 8 | color.b);
}

/*
 * Convert a 32-bit integer color value to a t_trgb color structure.
 *
 * This function extracts the transparency (t), red (r), green (g), and blue (b)
 * components from a 32-bit integer color value and constructs a t_trgb color
 * structure.
 *
 * Parameters:
 * - trgb: The 32-bit integer color value to be converted.
 *
 * Returns:
 * A t_trgb color structure with components extracted from the input integer.
 */
t_trgb	int_to_trgb(int trgb)
{
	t_trgb	color;

	color.t = (trgb >> 24) & 0xFF;
	color.r = (trgb >> 16) & 0xFF;
	color.g = (trgb >> 8) & 0xFF;
	color.b = (trgb) & 0xFF;
	return (color);
}
