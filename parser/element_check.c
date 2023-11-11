/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimouarrak <rimouarrak@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 22:51:16 by rimouarrak        #+#    #+#             */
/*   Updated: 2023/09/10 19:34:45 by rimouarrak       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	param_num(char *str)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			cpt++;
		i++;
	}
	return (cpt);
}

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

void	check_pl(char *str)
{
	if (param_num(str) != 3)
	{
		printf("Erros\nAnomalie in Planes (pl) parameters\n");
		exit (0);
	}
}

void	check_sp(char *str)
{
	if (param_num(str) != 3)
	{
		printf("Erros\nAnomalie in Spheres (sp) parameters\n");
		exit (0);
	}
}

void	check_cy(char *str)
{
	if (param_num(str) != 5)
	{
		printf("Erros\nAnomalie in Cylinders (cy) parameters\n");
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
		i++;
	}
}
