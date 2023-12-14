/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/11/23 15:10:43 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	clamp(double value, double min, double max)
{
	if (value < min)
		return (min);
	else if (value > max)
		return (max);
	else
		return (value);
}
