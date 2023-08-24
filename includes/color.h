/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:56:07 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/24 22:39:34 by aminebeihaq      ###   ########.fr       */
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

# include "minirt.h"

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
 * Create a color using TRGB components.
 *
 * This function creates and returns a color using the provided TRGB components.
 *
 * @param t The transparency component.
 * @param r The red component.
 * @param g The green component.
 * @param b The blue component.
 * @return The created color as a packed integer.
 */
int		create_trgb(int t, int r, int g, int b);

/**
 * Convert a t_trgb color to an integer representation.
 *
 * This function converts a t_trgb color structure into an integer representation.
 *
 * @param color The t_trgb color structure.
 * @return The color as a packed integer.
 */
int		trgb_to_int(t_trgb color);

/**
 * Convert an integer color to a t_trgb structure.
 *
 * This function converts an integer color representation into a t_trgb color structure.
 *
 * @param trgb The integer color representation.
 * @return The color as a t_trgb structure.
 */
t_trgb	int_to_trgb(int trgb);

#endif