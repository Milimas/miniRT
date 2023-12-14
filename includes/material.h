/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:21:58 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/11/23 17:17:35 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "vector.h"

/**
 * @struct t_material
 * @brief Represents the material properties of an object.
 *
 * This struct encapsulates the ambient, diffuse, and specular colors,
 * along with the shininess factor, defining the material properties of 
 * an object.
 *
 * @var t_material::ambient
 * The ambient color of the material.
 *
 * @var t_material::diffuse
 * The diffuse color of the material.
 *
 * @var t_material::specular
 * The specular color of the material.
 *
 * @var t_material::shininess
 * The shininess factor of the material.
 *
 * Use this struct to define and manage material properties for shading.
 */
typedef struct s_material
{
	t_color		ambient;
	t_color		diffuse;
	t_color		specular;
	double		shininess;
}	t_material;

#endif