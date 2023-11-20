/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rouarrak <rouarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:38:20 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/11/20 20:16:12 by rouarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file elements.h
 * @brief Header file for defining various elements in a 3D environment.
 *
 * This file contains declarations for structures representing different
 * elements such as ambient light, cameras, lights, spheres, planes, and
 * cylinders in a 3D environment.
 */

#ifndef ELEMENTS_H
# define ELEMENTS_H

# include "vector.h"
# include "color.h"
# include "material.h"

enum e_type
{
	NONE,
	CAMERA,
	PLANE,
	SPHERE,
	CYLINDER,
	CONE,
	POINT_LIGHT,
	AMBIENT_LIGHT,
	SPOT_LIGHT,
};

# include "ray.h"

/**
 * @struct t_ambient_light
 * @brief Represents ambient light in a 3D scene.
 *
 * This struct encapsulates the properties of ambient light, defining its
 * intensity ratio and color.
 *
 * @var t_ambient_light::ratio
 * The ambient light intensity ratio in the range [0.0, 1.0].
 *
 * @var t_ambient_light::color
 * Color represented by red (R), green (G), and blue (B) components,
 * each ranging from 0 to 255.
 *
 * Use this struct to define and manage ambient lighting properties.
 */
typedef struct s_ambient_light {
	double	ratio;
	t_color	color;
}	t_ambient_light;

typedef	struct s_axis
{
	t_vector	up;
	t_vector	right;
	t_vector	forward;
}	t_axis;

/**
 * @struct t_camera
 * @brief Represents a camera in 3D space.
 *
 * This struct encapsulates the properties of a camera, defining its position,
 * orientation, and field of view.
 *
 * @var t_camera::position
 * The position of the camera.
 *
 * @var t_camera::orientation
 * Orientation of the camera, with components in the range [-1, 1]
 * for each x, y, z axis.
 *
 * @var t_camera::fov
 * Horizontal field of view in degrees, in the range [0, 180].
 *
 * Use this struct to define and manage camera properties in a 3D environment.
 */
typedef struct s_camera {
	t_vector		position;
	t_vector		look_at;
	t_vector		dir;
	double			fov;
	double			aspect_ratio;
	double			width;
	double			height;
	t_vector		lower_left;
	t_vector		qx;
	t_vector		qy;
	t_axis			axis;
}	t_camera;

/**
 * @struct t_light
 * @brief Represents a light source in 3D space.
 *
 * This struct encapsulates the properties of a light source, defining its
 * position, brightness ratio, and color.
 *
 * @var t_light::position
 * The position of the light source.
 *
 * @var t_light::ratio
 * The light brightness ratio in the range [0.0, 1.0].
 *
 * @var t_light::color
 * (unused in mandatory part) R,G,B colors in the range [0-255].
 *
 * Use this struct to define and manage light sources within a 3D environment.
 */
typedef struct s_light {
	t_vector	position;
	double		ratio;
	t_color		color;
	t_vector	oc;
}	t_light;

/**
 * @struct t_sphere
 * @brief Represents a sphere in 3D space.
 *
 * This struct encapsulates the properties of a sphere, defining its position,
 * size, and color.
 *
 * @var t_sphere::position
 * The center position of the sphere.
 *
 * @var t_sphere::diameter
 * The diameter of the sphere.
 *
 * @var t_sphere::color
 * Color represented by red (R), green (G), and blue (B) components.
 *
 * Use this struct to create, manage, and render spheres within a 3D environment.
 */
typedef struct s_sphere {
	t_vector	position;
	double		radius;
	t_color		color;
}	t_sphere;

/**
 * @struct t_plane
 * @brief Represents a plane in 3D space.
 *
 * This struct encapsulates the properties of a plane, defined by its position,
 * normal direction, and color.
 *
 * @var t_plane::position
 * The position of a point in the plane.
 *
 * @var t_plane::normal
 * 3D normalized normal vector of the plane's surface.
 * Each component is in the range [-1, 1].
 *
 * @var t_plane::color
 * Color represented by red (R), green (G), and blue (B) components.
 *
 * Use this struct to create, manage, and render planes within a 3D environment.
 */
typedef struct s_plane {
	t_vector	position;
	t_vector	normal;
	t_color		color;
}	t_plane;

/**
 * @struct t_cylinder
 * @brief Represents a cylinder in 3D space.
 * 
 * This struct encapsulates the properties of a cylinder, allowing it to be
 * positioned, sized, oriented, and colored in a 3D scene.
 *
 * @var t_cylinder::position
 * The center position of the cylinder's base.
 *
 * @var t_cylinder::normal
 * 3D normalized vector of the cylinder's axis.
 * Each component is in the range [-1, 1].
 *
 * @var t_cylinder::diameter
 * The diameter of the cylinder.
 *
 * @var t_cylinder::height
 * The height of the cylinder.
 *
 * @var t_cylinder::color
 * Color represented by red (R), green (G), and blue (B) components.
 * 
 * Use this struct to create, manage, and render cylinders within a 3D
 * environment.
 */

typedef struct s_cylinder {
	t_vector	position;
	t_vector	normal;
	double		radius;
	double		height;
	t_color		color;
}	t_cylinder;

typedef struct s_cone {
	t_vector	position;
	t_vector	normal;
	// double		radius;
	double		angle;
	double		height;
	t_color		color;
}	t_cone;

typedef	struct s_object
{
	union
	{
		t_plane		*plane;
		t_sphere	*sphere;
		t_cylinder	*cylinder;
		t_cone		*cone;
		t_light		*spot;
	};
	void			*texture;
	bool			checkerboard;
	t_material		material;
	t_vector		oc;
	enum e_type		type;
	struct s_object	*next;
}	t_object;

/**
 * @struct t_scene
 * @brief Represents a scene in a 3D environment.
 *
 * This structure encapsulates the elements of a 3D scene, including lists of
 * cameras, lights, planes, triangles, spheres, squares, and cylinders.
 *
 * @var t_scene::cameras
 * List of cameras in the scene.
 *
 * @var t_scene::lights
 * List of lights in the scene.
 *
 * @var t_scene::planes
 * List of planes in the scene.
 *
 * @var t_scene::triangles
 * List of triangles in the scene.
 *
 * @var t_scene::spheres
 * List of spheres in the scene.
 *
 * @var t_scene::squares
 * List of squares in the scene.
 *
 * @var t_scene::cylinders
 * List of cylinders in the scene.
 *
 * Use this structure to define and manage a complete 3D scene.
 */
typedef struct s_scene {
	t_camera		*camera;
	t_ambient_light	*ambient;
	t_light			*light;
	t_object		*spots;
	t_object		*objs;
}	t_scene;

typedef struct s_spots {
	t_vector	position;
	t_vector	direction;
	double		degree;
	t_color		color;
}	t_spots;

double	cylinder_int(t_ray *ray, t_object *objs);
double	light_int(t_ray *ray, t_light *light);
double	plane_int(t_ray *ray, t_object *objs);
double	sphere_int(t_ray *ray, t_object *objs);

double	cone_int(t_ray *ray, t_object *objs);

#endif