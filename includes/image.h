/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:08:22 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/11/23 17:10:24 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file image.h
 * @brief Header file for image-related functions and structures.
 *
 * This file contains declarations for functions and structures related to
 * managing and manipulating images in graphics rendering.
 */

#ifndef IMAGE_H
# define IMAGE_H

# include "minirt.h"

typedef struct s_window	t_window;

/**
 * @struct t_img
 * @brief Represents an image in a graphics rendering window.
 *
 * This structure encapsulates the properties of an image, including its
 * image pointer, pixel address, bits per pixel, size of each line, endianness,
 * height, and width.
 *
 * @var t_img::img_ptr
 * A pointer to the image.
 *
 * @var t_img::addr
 * A pointer to the pixel address of the image.
 *
 * @var t_img::bits_per_pixel
 * The number of bits used to represent each pixel in the image.
 *
 * @var t_img::size_line
 * The size of each line in the image.
 *
 * @var t_img::endian
 * The endianness of the image.
 *
 * @var t_img::height
 * The height of the image.
 *
 * @var t_img::width
 * The width of the image.
 *
 * Use this struct to define and manage image properties in a graphics 
 * rendering window.
 */
typedef struct s_img {
	void		*img_ptr;
	int			*addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			height;
	int			width;
}	t_img;

/**
 * @brief Clear the image data in a graphics rendering window.
 *
 * This function sets all the pixel values in the image associated with the
 * given graphics rendering window to zero. The image data is effectively
 * cleared.
 *
 * @param window Pointer to the graphics rendering window (t_window) to clear.
 */
void	clear_mlx_image(t_window *window);

#endif
