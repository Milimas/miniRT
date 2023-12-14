/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/08/23 20:17:53 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	solve_quadratic(t_quadratic *res, double t)
{
	res->t[0] = INFINITY;
	res->t[1] = INFINITY;
	res->delta = sqrt(res->b * res->b - res->a * res->c);
	if (res->delta < 0)
		return ;
	res->t[0] = (-res->b - res->delta) / res->a;
	res->t[1] = (-res->b + res->delta) / res->a;
	res->hit[0] = (res->t[0] > ELIPS && res->t[0] < t);
	res->hit[1] = (res->t[1] > ELIPS && res->t[1] < t);
}
