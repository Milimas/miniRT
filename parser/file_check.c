/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimouarrak <rimouarrak@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:39:49 by rimouarrak        #+#    #+#             */
/*   Updated: 2023/09/10 19:38:11 by rimouarrak       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

static void	elem_dup_error(int cptA, int cptC, int cptL)
{
	if (cptA == 0 || cptC == 0 || cptL == 0)
	{
		printf("Error\nThere is a missing element\n");
		exit (0);
	}
	if (cptA > 1 || cptC > 1 || cptL > 1)
	{
		printf("Error\nElements that start with an uppercase"
			"letter can only be declared once in the scene.\n");
		exit (0);
	}
}

void	check_elem_dup(char **tab)
{
	int	cpta;
	int	cptc;
	int	cptl;

	cpta = 0;
	cptc = 0;
	cptl = 0;
	while (*tab)
	{
		if (**tab == 'A')
			cpta++;
		else if (**tab == 'C')
			cptc++;
		else if (**tab == 'L')
			cptl++;
		tab++;
	}
	elem_dup_error(cpta, cptc, cptl);
}

static int	make_set(char *str)
{
	int		i;
	int		cpt;
	char	**set;

	i = 0;
	cpt = 0;
	set = ft_calloc(8, sizeof(char *));
	set[0] = ft_strdup("A");
	set[1] = ft_strdup("C");
	set[2] = ft_strdup("L");
	set[3] = ft_strdup("pl");
	set[4] = ft_strdup("sp");
	set[5] = ft_strdup("cy");
	set[6] = ft_strdup("cn");
	set[7] = NULL;
	while (set[i])
	{
		if (!ft_strcmp(str, set[i]))
			cpt++;
		i++;
	}
	free_split(set);
	return (cpt);
}

void	check_imposter(char **tab)
{
	int		i;
	char	**str;

	i = 0;
	while (tab[i])
	{
		str = ft_split(tab[i], ' ');
		if (!make_set(str[0]))
		{
			printf("Error\nThere is an unknown element\n");
			free_split(str);
			exit (0);
		}
		i++;
		free_split(str);
	}
}

void	supervisor(char	**tab)
{
	check_imposter(tab);
	check_elem_dup(tab);
	check_elements(tab);
}
