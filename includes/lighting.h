/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:56:07 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/24 23:40:09 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H

#include "ray.h"
#include "vector.h"
#include "elements.h"

t_color	ambient(t_ray *ray, t_ambient_light amb);
t_color	diffuse(t_ray *ray, t_light light);
t_color	specular(t_ray *ray, t_light light);
t_color	apply_light(t_color surface, t_color light);

#endif