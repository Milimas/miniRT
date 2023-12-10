/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimouarrak <rimouarrak@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 06:39:53 by rouarrak          #+#    #+#             */
/*   Updated: 2023/12/10 23:00:32 by rimouarrak       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	ft_isnum(char *str)
{
	int		i;
	char	*num;

	i = 0;
	num = NULL;
	if (ft_strchr(str, '\n'))
		num = rm_n(str);
	else
		num = ft_strdup(str);
	while (num[i])
	{
		if (!ft_isdigit(num[i]) && num[i] != '0')
		{
			free(num);
			return (0);
		}
		i++;
	}
	free(num);
	return (1);
}

void	tree_num(char **param)
{
	if (ft_isnum(param[0]) == 0 || ft_isnum(param[1]) == 0
		|| ft_isnum(param[2]) == 0)
	{
		printf("Error\nAn parameter must be a number check it!\n");
		free_split(param);
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
		free_split(rgb);
		exit (0);
	}
	tree_num(rgb);
	r = (double)ft_atoi(rgb[0]) / 0xFF;
	g = (double)ft_atoi(rgb[1]) / 0xFF;
	b = (double)ft_atoi(rgb[2]) / 0xFF;
	if (! (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255))
	{
		printf("Error\nThe RGB values should be between 0 and 255\n");
		free_split(rgb);
		exit (0);
	}
}

void	check_ort(char **ort)
{
	double	x;
	double	y;
	double	z;

	if (!ort)
		exit(1);
	if ((!(ort[0] && ort[1] && ort[2])) || ort[3] != NULL)
	{
		printf("Error\nSomething is wrong in orientation parameter\n");
		free_split(ort);
		exit (0);
	}
	x = str_to_double(ort[0]);
	y = str_to_double(ort[1]);
	z = str_to_double(ort[2]);
	if (! (x >= -1 && x <= 1 && y >= -1 && y <= 1 && z >= -1 && z <= 1))
	{
		printf("Error\nThe 3d normalized orientation vector should"
			" be in range [-1,1] for each x,y,z axis\n");
		free_split(ort);
		exit (0);
	}
}

void	check_pos(char **pos)
{
	if (!pos)
		exit(1);
	if ((!(pos[0] && pos[1] && pos[2])) || pos[3] != NULL)
	{
		printf("Error\nSomething is wrong in position parameter\n");
		free_split(pos);
		exit (0);
	}
	str_to_double(pos[0]);
	str_to_double(pos[1]);
	str_to_double(pos[2]);
}
