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

int ft_isnum(char *num)
{
	int i;

	i = 0;
	while(num[i])
	{
		if (!ft_isdigit(num[i]) && num[i] != '0')
			return (0);
		i++;
	}
	return (1);
}

void	tree_num(char **param)
{
	char	*paramn;

	if (ft_isnum(param[0]) == 0 || ft_isnum(param[1]) == 0)
	{
		printf("Error\nAn parameter must be a number check it!\n");
		exit(0);
	}
	if (ft_strchr(param[2], '\n'))
	{	
		paramn = rm_n(param[2]);
		if (ft_isnum(paramn) == 0)
		{
			printf("Error\nAn parameter must be a number check it!\n");
			free (paramn);
			exit(0);
		}
		free (paramn);
	}
	else if (ft_isnum(param[2]) == 0)
	{
		printf("Error\nAn parameter must be a number check it!\n");
		exit(0);
	}

}

void	check_rgb(char **rgb)
{
	double	r;
	double	g;
	double	b;

	if (!rgb)
		exit(1);
	if (!((rgb[0] && rgb[1] && rgb[2]) && rgb[2][0] != '\n' && !rgb[3]))
	{
		printf("Error\nSomething is wrong in RGB parameter\n");
		exit (0);
	}
	tree_num(rgb);
	r = (double)ft_atoi(rgb[0]) / 0xFF;
	g = (double)ft_atoi(rgb[1]) / 0xFF;
	b = (double)ft_atoi(rgb[2]) / 0xFF;
	if (! (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255))
	{
		printf("Error\nThe RGB values should be between 0 and 255\n");
		exit (0);
	}
}

void	check_ort(char **ort)
{
	double	x;
	double	y;
	double	z;

	if (!ort)
	{
		printf("Error\nMalloc error\n");
		exit(1);
	}
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

void	check_pos(char **pos)
{
	if (!pos)
	{
		printf("Error\nMalloc error\n");
		exit(1);
	}
	tree_num(pos);
}