/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:10:47 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/23 20:13:57 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/*
 * Clear the image data in a graphics rendering window.
 *
 * This function sets all the pixel values in the image associated with the
 * given graphics rendering window to zero. The image data is effectively
 * cleared.
 *
 * Parameters:
 * - window: Pointer to the graphics rendering window (t_window) to clear.
 */
void	clear_mlx_image(t_window *window)
{
	ft_bzero(window->img.addr, WIN_HEIGHT * WIN_WIDTH * sizeof(int));
}
