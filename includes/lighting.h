/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:56:07 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/11/23 13:17:14 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H

# include "ray.h"
# include "vector.h"
# include "elements.h"

t_color	ambient(t_ray *ray, t_ambient_light amb);
t_color	diffuse(t_ray *ray, t_light light);
t_color	specular(t_ray *ray, t_light light);
t_color	apply_light(t_color surface, t_color light);
void	shadow(t_ray *ray, t_window *window);

#endif