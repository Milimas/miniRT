/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:08:22 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/24 22:40:49 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"
# include <math.h>

typedef union u_matrix
{
    double m[4][4];
    struct {
      t_vector r1;
      t_vector r2;
      t_vector r3;
      t_vector r4;
    };
} t_matrix;

t_matrix matrix_rot_x(double angle);
t_matrix matrix_rot_y(double angle);
t_matrix matrix_rot_z(double angle);

t_vector    dir_matrix(t_vector v, t_matrix m);

#endif