/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouarrak <rouarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 22:51:16 by rouarrak        #+#    #+#             */
/*   Updated: 2023/11/24 05:34:25 by rouarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	check_a(char *str)
{
	if (param_num(str) != 2)
	{
		printf("Erros\nAnomalie in ambient light (A) parameters\n");
		exit (0);
	}
}

void	check_c(char *str)
{
	if (param_num(str) != 3)
	{
		printf("Erros\nAnomalie in Cameras (C) parameters\n");
		exit (0);
	}
}

void	check_l(char *str)
{
	if (param_num(str) != 3)
	{
		printf("Erros\nAnomalie in Lights (L) parameters\n");
		exit (0);
	}
}

void	check_sl(char *str)
{
	if (!(param_num(str) == 3))
	{
		printf("Erros\nAnomalie in Spot Lights (sp) parameters\n");
		exit (0);
	}
}

void	check_elements(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], "A", 1))
			check_a(tab[i]);
		else if (!ft_strncmp(tab[i], "C", 1))
			check_c(tab[i]);
		else if (!ft_strncmp(tab[i], "L", 1))
			check_l(tab[i]);
		else if (!ft_strncmp(tab[i], "pl", 2))
			check_pl(tab[i]);
		else if (!ft_strncmp(tab[i], "sp", 2))
			check_sp(tab[i]);
		else if (!ft_strncmp(tab[i], "cy", 2))
			check_cy(tab[i]);
		else if (!ft_strncmp(tab[i], "cn", 2))
			check_cn(tab[i]);
		else if (!ft_strncmp(tab[i], "sl", 2))
			check_sl(tab[i]);
		i++;
	}
}
