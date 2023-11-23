/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:23:40 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/11/23 15:05:25 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * @brief Set the color of a pixel in the image data.
 *
 * This function sets the color of a pixel at the specified coordinates (x, y)
 *  in the given image data. The provided color value is applied to the pixel.
 *
 * @param data Pointer to the image data (t_img) where the pixel color will
 * be set.
 * @param pixel The pixel's position (x, y).
 * @param color The color value to be applied to the pixel.
 */
void	put_pixel(t_img *data, t_pixel pixel, int color)
{
	char	*dst;

	dst = (char *)data->addr
		+ ((int)pixel.y * data->size_line
			+ (int)pixel.x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_pixel_color(t_img *data, t_pixel pixel)
{
	char	*dst;

	dst = (char *)data->addr
		+ ((int)pixel.y * data->size_line
			+ (int)pixel.x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}
