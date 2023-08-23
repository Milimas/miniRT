/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:56:07 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/23 20:05:58 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "minirt.h"

/*
 * Structure representing color in the form of TRGB values.
 *
 * This struct encapsulates the components of a color, using TRGB values
 * where each component ranges from 0 to 255.
 *
 * Members:
 * - t: The transparency component of the color.
 * - r: The red component of the color.
 * - g: The green component of the color.
 * - b: The blue component of the color.
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

int		create_trgb(int t, int r, int g, int b);
int		trgb_to_int(t_trgb color);
t_trgb	int_to_trgb(int trgb);

#endif