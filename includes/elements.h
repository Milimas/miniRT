/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:38:20 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/19 22:21:03 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENTS_H
# define ELEMENTS_H

# include "minirt.h"

/*
 * Structure representing ambient light in a 3D scene.
 *
 * This struct encapsulates the properties of ambient light, defining its
 * intensity ratio and color.
 *
 * Members:
 * - ratio: The ambient light intensity ratio in the range [0.0, 1.0].
 * - color: Color represented by red (R), green (G), and blue (B) components,
 *          each ranging from 0 to 255.
 *
 * Use this struct to define and manage ambient lighting properties.
 */
typedef struct s_ambient_light {
	double	ratio;
	t_trgb	color;
}	t_ambient_light;

/*
 * Structure representing a camera in 3D space.
 *
 * This struct encapsulates the properties of a camera, defining its position,
 * orientation, and field of view.
 *
 * Members:
 * - position: The position of the camera.
 * - orientation: Orientation of the camera, with components in the range [-1, 1]
 *                for each x, y, z axis.
 * - fov: Horizontal field of view in degrees, in the range [0, 180].
 *
 * Use this struct to define and manage camera properties in a 3D environment.
 */
typedef struct s_camera {
	t_vector		position;
	t_vector		orientation;
	unsigned int	fov;
}	t_camera;

/*
 * Structure representing a light source in 3D space.
 *
 * This struct encapsulates the properties of a light source, defining its
 * position, brightness ratio, and color.
 *
 * Members:
 * - position: The position of the light source.
 * - ratio: The light brightness ratio in the range [0.0, 1.0].
 * - color: (unused in mandatory part) R,G,B colors in the range [0-255].
 *
 * Use this struct to define and manage light sources within a 3D environment.
 */
typedef struct s_light {
	t_vector	position;
	double		ratio;
	t_trgb		color;
}	t_light;

/*
 * Structure representing a sphere in 3D space.
 *
 * This struct encapsulates the properties of a sphere, defining its position,
 * size, and color.
 *
 * Members:
 * - position: The center position of the sphere.
 * - diameter: The diameter of the sphere.
 * - color: Color represented by red (R), green (G), and blue (B) components,
 *          each ranging from 0 to 255.
 *
 * Use this struct to create, manage, and render spheres within a 3D environment.
 */
typedef struct s_sphere {
	t_vector	position;
	double		diameter;
	t_trgb		color;
}	t_sphere;

/*
 * Structure representing a plane in 3D space.
 *
 * This struct encapsulates the properties of a plane, defined by its position,
 * normal direction, and color.
 *
 * Members:
 * - position: The position of a point in the plane.
 * - normal: 3D normalized normal vector of the plane's surface.
 *           Each component is in the range [-1, 1].
 * - color: Color represented by red (R), green (G), and blue (B) components,
 *          each ranging from 0 to 255.
 *
 * Use this struct to create, manage, and render planes within a 3D environment.
 */
typedef struct s_plane {
	t_vector	position;
	t_vector	normal;
	t_trgb		color;
}	t_plane;

/*
 * Structure representing a cylinder in 3D space.
 * 
 * This struct encapsulates the properties of a cylinder, allowing it to be
 * positioned, sized, oriented, and colored in a 3D scene.
 * 
 * Members:
 * - position: The center position of the cylinder's base.
 * - normal: 3D normalized vector of the cylinder's axis.
 *           Each component is in the range [-1, 1].
 * - diameter: The diameter of the cylinder.
 * - height: The height of the cylinder.
 * - color: Color represented by red (R), green (G), and blue (B) components,
 *          each ranging from 0 to 255.
 * 
 * Notes:
 * - The 'position' and 'normal' vectors collectively define the cylinder's
 *   placement and orientation in the scene.
 * - 'diameter' determines the width of the cylinder.
 * - 'height' specifies the extent along the axis direction.
 * - 'color' represents the visual appearance of the cylinder.
 * 
 * Use this struct to create, manage, and render cylinders within a 3D
 * environment.
 */
typedef struct s_cylinder {
	t_vector	position;
	t_vector	normal;
	double		diameter;
	double		height;
	t_trgb		color;
}	t_cylinder;

#endif