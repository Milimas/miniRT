/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:08:22 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/11/23 15:11:59 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/matrix.h"

t_vector	dir_matrix(t_vector v, t_matrix m)
{
	t_vector	res;

	res.x = v.x * m.m[0][0] + v.y * m.m[0][1] + v.z * m.m[0][2];
	res.y = v.x * m.m[1][0] + v.y * m.m[1][1] + v.z * m.m[1][2];
	res.z = v.x * m.m[2][0] + v.y * m.m[2][1] + v.z * m.m[2][2];
	return (res);
}

t_vector	v4_matrix(t_vector4 v, t_matrix m)
{
	t_vector4	res;
	t_vector	res3;

	res.x = v.x * m.m[0][0] + v.y * m.m[0][1]
		+ v.z * m.m[0][2] + v.w * m.m[0][3];
	res.y = v.x * m.m[1][0] + v.y * m.m[1][1]
		+ v.z * m.m[1][2] + v.w * m.m[1][3];
	res.z = v.x * m.m[2][0] + v.y * m.m[2][1]
		+ v.z * m.m[2][2] + v.w * m.m[2][3];
	res.w = v.x * m.m[3][0] + v.y * m.m[3][1]
		+ v.z * m.m[3][2] + v.w * m.m[3][3];
	res3.x = res.x / res.w;
	res3.y = res.y / res.w;
	res3.z = res.z / res.w;
	return (res3);
}
