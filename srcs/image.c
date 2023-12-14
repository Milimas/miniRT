/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:10:47 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/08/24 22:44:27 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * @brief Clear the image data in a graphics rendering window.
 *
 * This function sets all the pixel values in the image associated with the
 * given graphics rendering window to zero. The image data is effectively
 * cleared.
 *
 * @param window Pointer to the graphics rendering window (t_window) to clear.
 */
void	clear_mlx_image(t_window *window)
{
	ft_bzero(window->img.addr, WIN_HEIGHT * WIN_WIDTH * sizeof(int));
}
