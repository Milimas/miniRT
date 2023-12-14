/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:56:07 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/11/23 17:16:52 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H

# include "ray.h"
# include "vector.h"
# include "elements.h"

/**
 * @brief Calculate the ambient component of the shading.
 *
 * @param ray   Pointer to the ray structure.
 * @param amb   The ambient light in the scene.
 * @return      The color of the ambient component.
 */
t_color	ambient(t_ray *ray, t_ambient_light amb);

/**
 * @brief Calculate the diffuse component of the shading.
 *
 * @param ray    Pointer to the ray structure.
 * @param light  The light source in the scene.
 * @return       The color of the diffuse component.
 */
t_color	diffuse(t_ray *ray, t_light light);

/**
 * @brief Calculate the specular component of the shading.
 *
 * @param ray    Pointer to the ray structure.
 * @param light  The light source in the scene.
 * @return       The color of the specular component.
 */
t_color	specular(t_ray *ray, t_light light);

/**
 * @brief Apply the lighting effects to the surface color.
 *
 * @param surface  The color of the surface.
 * @param light    The color of the light.
 * @return         The final color after applying lighting effects.
 */
t_color	apply_light(t_color surface, t_color light);

/**
 * @brief Calculate the shading, including ambient, diffuse, specular, 
 * and shadows.
 *
 * This function calculates the ambient, diffuse, and specular components of
 * the shading for a given ray, considering the lighting conditions and
 * checks for shadows. It then applies the calculated light to the surface color.
 *
 * @param ray      Pointer to the ray structure.
 * @param window   Pointer to the graphics rendering window.
 */
void	shadow(t_ray *ray, t_window *window);

#endif