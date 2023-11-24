/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_check_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouarrak <rouarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 05:33:33 by rouarrak          #+#    #+#             */
/*   Updated: 2023/11/24 05:34:43 by rouarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	check_sp(char *str)
{
	if (!(param_num(str) == 3 || param_num(str) == 4))
	{
		printf("Erros\nAnomalie in Spheres (sp) parameters\n");
		exit (0);
	}
}

void	check_cy(char *str)
{
	if (!(param_num(str) == 5 || param_num(str) == 6))
	{
		printf("Erros\nAnomalie in Cylinders (cy) parameters\n");
		exit (0);
	}
}

void	check_cn(char *str)
{
	if (!(param_num(str) == 5 || param_num(str) == 6))
	{
		printf("Erros\nAnomalie in Cylinders (cy) parameters\n");
		exit (0);
	}
}

void	check_pl(char *str)
{
	if (!(param_num(str) == 3 || param_num(str) == 4))
	{
		printf("Erros\nAnomalie in Planes (pl) parameters\n");
		exit (0);
	}
}
