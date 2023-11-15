/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:34:07 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/23 20:17:53 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/matrix.h"

t_matrix matrix_rot_x(double angle)
{
    double  rad;

    rad = angle * M_PI / 180;
    t_matrix rot_x = {{
        {1,0,0,0},
        {0,cos(rad),-sin(rad),0},
        {0,sin(rad),cos(rad),0},
        {0,0,0,1},
    }};
    return rot_x;
}

t_matrix matrix_rot_z(double angle)
{
    double  rad;

    rad = angle * M_PI / 180;
    t_matrix rot_z = {{
        {cos(rad), -sin(rad), 0, 0},
        {sin(rad), cos(rad), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    }};
    return rot_z;
}

t_matrix matrix_rot_y(double angle)
{
    double  rad;

    rad = angle * M_PI / 180;
    t_matrix rot_x = {{
        {cos(rad), 0, sin(rad), 0},
        {0, 1, 0, 0},
        {-sin(rad), 0, cos(rad), 0},
        {0, 0, 0, 1},
    }};
    return rot_x;
}