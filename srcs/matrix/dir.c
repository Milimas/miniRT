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

#include "../../includes/matrix.h"

t_vector    dir_matrix(t_vector v, t_matrix m)
{
    t_vector res;
    
    res.x = v.x * m.m[0][0] + v.y * m.m[0][1] + v.z * m.m[0][2];
    res.y = v.x * m.m[1][0] + v.y * m.m[1][1] + v.z * m.m[1][2];
    res.z = v.x * m.m[2][0] + v.y * m.m[2][1] + v.z * m.m[2][2];
    
    return (res);
}