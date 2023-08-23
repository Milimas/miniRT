/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:23:40 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/23 20:02:21 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/*
 * Set the color of a pixel in the image data.
 *
 * This function sets the color of a pixel at the specified coordinates (x, y) in
 * the given image data. The provided color value is applied to the pixel.
 *
 * Parameters:
 * - data: Pointer to the image data (t_img) where the pixel color will be set.
 * - pixel: The pixel's position (x, y).
 * - color: The color value to be applied to the pixel.
 */
void	put_pixel(t_img *data, t_pixel pixel, int color)
{
	int	(*dst)[WIN_WIDTH][1];

	if (pixel.x >= WIN_WIDTH || pixel.y >= WIN_HEIGHT
		|| pixel.x < 0 || pixel.y < 0)
		return ;
	dst = (void *)data->addr;
	*dst[pixel.y][pixel.x] = color;
}
