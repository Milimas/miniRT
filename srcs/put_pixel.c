/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:23:40 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/19 22:26:22 by aminebeihaq      ###   ########.fr       */
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
 * - x: The x-coordinate of the pixel.
 * - y: The y-coordinate of the pixel.
 * - color: The color value to be applied to the pixel.
 */
void	put_pixel(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x > WIN_WIDTH || y > WIN_HEIGHT || x < 0 || y < 0)
		return ;
	dst = data->addr + (y * data->size_line + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
