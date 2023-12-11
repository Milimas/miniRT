/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouarrak <rouarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:38:57 by rouarrak        #+#    #+#             */
/*   Updated: 2023/11/24 06:42:28 by rouarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_object	*last_obj(t_object *head)
{
	while (head && head->next)
		head = head->next;
	return (head);
}

void	append_object(t_object **head, t_object *new)
{
	if (!*head)
		*head = new;
	else
		last_obj(*head)->next = new;
}

void	init_struct(t_scene *scene)
{
	scene->ambient = ft_calloc(1, sizeof(t_ambient_light));
	scene->camera = ft_calloc(1, sizeof(t_camera));
	scene->light = ft_calloc(1, sizeof(t_light));
}

void	fill_elm(char	**tab, t_window *win)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], "A", 1))
			fill_a(tab[i], win);
		else if (!ft_strncmp(tab[i], "C", 1))
			fill_c(tab[i], win);
		else if (!ft_strncmp(tab[i], "L", 1))
			fill_l(tab[i], win);
		else if (!ft_strncmp(tab[i], "pl", 2))
			fill_pl(tab[i], win);
		else if (!ft_strncmp(tab[i], "sp", 2))
			fill_sp(tab[i], win);
		else if (!ft_strncmp(tab[i], "cy", 2))
			fill_cy(tab[i], win);
		else if (!ft_strncmp(tab[i], "cn", 2))
			fill_cn(tab[i], win);
		else if (!ft_strncmp(tab[i], "sl", 2))
			fill_sl(tab[i], win);
		i++;
	}
}
