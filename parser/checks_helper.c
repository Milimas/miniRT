/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouarrak <rouarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 06:39:53 by rouarrak          #+#    #+#             */
/*   Updated: 2023/11/24 06:42:34 by rouarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	check_ort(char **ort)
{
	double	x;
	double	y;
	double	z;

	x = str_to_double(ort[0]);
	y = str_to_double(ort[1]);
	z = str_to_double(ort[2]);
	if (! (x >= -1 && x <= 1 && y >= -1 && y <= 1 && z >= -1 && z <= 1))
	{
		printf("Error\nThe 3d normalized orientation vector should"
			" be in range [-1,1] for each x,y,z axis\n");
		exit (0);
	}
}

void	check_rgb(char **rgb)
{
	double	r;
	double	g;
	double	b;

	if (!((rgb[0] && rgb[1] && rgb[2]) && rgb[2][0] != '\n' && !rgb[3]))
	{
		printf("Error\nSomething is wrong in RGB parameter\n");
		exit (0);
	}
	r = (double)ft_atoi(rgb[0]) / 0xFF;
	g = (double)ft_atoi(rgb[1]) / 0xFF;
	b = (double)ft_atoi(rgb[2]) / 0xFF;
	if (! (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255))
	{
		printf("Error\nThe RGB values should be between 0 and 255\n");
		exit (0);
	}
}
