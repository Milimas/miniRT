/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:56:07 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/11/23 16:44:05 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file color.h
 * @brief Header file for defining color-related structures and functions.
 *
 * This file contains declarations for a color structure using TRGB values and
 * functions for creating, converting, and managing colors.
 */

#ifndef COLOR_H
# define COLOR_H

# include "elements.h"

typedef struct s_object	t_object;

/**
 * @struct t_trgb
 * @brief Represents color in the form of TRGB values.
 *
 * This struct encapsulates the components of a color, using TRGB values
 * where each component ranges from 0 to 255.
 *
 * @var t_trgb::t
 * The transparency component of the color.
 *
 * @var t_trgb::r
 * The red component of the color.
 *
 * @var t_trgb::g
 * The green component of the color.
 *
 * @var t_trgb::b
 * The blue component of the color.
 *
 * Use this struct to define and manage colors with TRGB values.
 * Note: TRGB ranges are [0, 255] for each component.
 */
typedef struct s_trgb
{
	unsigned char	t;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_trgb;

/**
 * Convert a t_trgb color to an integer representation.
 *
 * This function converts a t_trgb color structure
 * into an integer representation.
 *
 * @param color The t_trgb color structure.
 * @return The color as a packed integer.
 */
int		trgb_to_int(t_trgb color);

/**
 * Mix two colors based on a given ratio.
 *
 * This function blends two colors (m and l) based on a specified ratio.
 *
 * @param m The color to be mixed.
 * @param l The background color.
 * @param ratio The blending ratio (0.0 to 1.0).
 * @return The resulting color after blending.
 */
t_trgb	mix_trgb(t_trgb m, t_trgb l, double ratio);

/**
 * Convert a 3D vector color to an RGB color.
 *
 * This function converts a t_color structure representing a 3D vector color
 * into an RGB color (t_trgb).
 *
 * @param vec The 3D vector color.
 * @return The corresponding RGB color.
 */
t_trgb	vec_to_rgb(t_color vec);

/**
 * Get the color of an object.
 *
 * This function retrieves the color of a given object.
 *
 * @param obj The object from which to retrieve the color.
 * @return The color of the object.
 */
t_color	get_color(t_object obj);

/**
 * Convert an RGB color to a 3D vector color.
 *
 * This function converts an RGB color (t_trgb) into a 3D vector color (t_color).
 *
 * @param color The RGB color to be converted.
 * @return The corresponding 3D vector color.
 */
t_color	rgb_to_vec(t_trgb color);

/**
 * Convert an integer representation to a t_color structure.
 *
 * This function converts an integer color representation to a t_color structure.
 *
 * @param trgb The integer color representation.
 * @return The color as a t_color structure.
 */
t_color	int_to_color(int trgb);

#endif