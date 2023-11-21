/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:08:22 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/24 22:40:49 by aminebeihaq      ###   ########.fr       */
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
 * @struct s_img
 * @brief Represents an image for graphics rendering.
 *
 * This struct encapsulates properties of an image, such as its pointer,
 * address, bits per pixel, size per line, and endianness.
 *
 * @var s_img::img_ptr
 * Pointer to the image.
 * 
 * @var s_img::addr
 * Address of the image.
 * 
 * @var s_img::bits_per_pixel
 * Number of bits per pixel.
 * 
 * @var s_img::size_line
 * Size per line of the image.
 * 
 * @var s_img::endian
 * Endianness of the image.
 *
 * Use this struct to manage image properties in graphics rendering.
 */
typedef struct s_img {
	void	*img_ptr;
	int		*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
    int     height;
    int     width;
}	t_img;

/**
 * @brief Clear the image data in a graphics rendering window.
 *
 * This function sets all the pixel values in the image associated with the
 * given graphics rendering window to zero. The image data is effectively cleared.
 *
 * @param window Pointer to the graphics rendering window (t_window) to clear.
 */
void	clear_mlx_image(t_window *window);

#endif
