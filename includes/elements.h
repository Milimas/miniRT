/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:38:20 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/11/23 17:06:10 by aminebeihaq      ###   ########.fr       */
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
# include "image.h"
# include "ray.h"

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

/**
 * @struct t_axis
 * @brief Represents an axis with up, right, and forward vectors.
 *
 * This structure encapsulates the three vectors representing an axis:
 * up, right, and forward.
 *
 * @var t_axis::up
 * The up vector of the axis.
 *
 * @var t_axis::right
 * The right vector of the axis.
 *
 * @var t_axis::forward
 * The forward vector of the axis.
 *
 * Use this struct to represent and manage 3D axes.
 */
typedef struct s_axis
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
 * @var t_camera::dir
 * The point the camera is looking at.
 *
 * @var t_camera::fov
 * Horizontal field of view in degrees, in the range [0, 180].
 *
 * @var t_camera::aspect_ratio
 * The aspect ratio of the camera.
 *
 * @var t_camera::width
 * The width of the camera's viewport.
 *
 * @var t_camera::height
 * The height of the camera's viewport.
 *
 * @var t_camera::lower_left
 * The lower-left corner of the camera's viewport.
 *
 * @var t_camera::u
 * The vector reprventing the change in x direction of the camera.
 *
 * @var t_camera::qy
 * The vector representing the change in y direction of the camera.
 *
 * @var t_camera::axis
 * The axis of the camera, including up, right, and forward vectors.
 *
 * Use this struct to define and manage camera properties in a 3D environment.
 */
typedef struct s_camera {
	t_vector		position;
	t_vector		dir;
	double			fov;
	double			aspect_ratio;
	double			width;
	double			height;
	t_vector		lower_left;
	t_vector		u;
	t_vector		v;
	t_axis			axis;
}	t_camera;

/**
 * @struct t_light
 * @brief Represents a light source in 3D space.
 *
 * This struct encapsulates the properties of a light source, defining its
 * position, brightness ratio, color, and the vector from the light to the
 * intersection point.
 *
 * @var t_light::position
 * The position of the light source.
 *
 * @var t_light::ratio
 * The light brightness ratio in the range [0.0, 1.0].
 *
 * @var t_light::color
 * Color of the light.
 *
 * @var t_light::oc
 * The vector from the light source to the intersection point.
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

/**
 * @struct t_cone
 * @brief Represents a cone in 3D space.
 *
 * This struct encapsulates the properties of a cone, defining its position,
 * orientation, angle, height, and color.
 *
 * @var t_cone::position
 * The center position of the cone's base.
 *
 * @var t_cone::normal
 * 3D normalized vector of the cone's axis.
 * Each component is in the range [-1, 1].
 *
 * @var t_cone::angle
 * The angle of the cone.
 *
 * @var t_cone::height
 * The height of the cone.
 *
 * @var t_cone::color
 * Color represented by red (R), green (G), and blue (B) components.
 *
 * Use this struct to create, manage, and render cones within a 3D environment.
 */
typedef struct s_cone {
	t_vector	position;
	t_vector	normal;
	double		angle;
	double		height;
	t_color		color;
}	t_cone;

/**
 * @struct t_object
 * @brief Represents an object in a 3D environment.
 *
 * This structure encapsulates various elements such as planes, spheres,
 * cylinders, cones, and lights. It uses a union to handle different 
 * object types.
 *
 * @var t_object::plane
 * Pointer to a plane object if the type is PLANE.
 *
 * @var t_object::sphere
 * Pointer to a sphere object if the type is SPHERE.
 *
 * @var t_object::cylinder
 * Pointer to a cylinder object if the type is CYLINDER.
 *
 * @var t_object::cone
 * Pointer to a cone object if the type is CONE.
 *
 * @var t_object::spot
 * Pointer to a light source object if the type is SPOT_LIGHT.
 *
 * @var t_object::texture
 * Image data for texture mapping.
 *
 * @var t_object::checkerboard
 * Boolean flag indicating whether the object has a checkerboard pattern.
 *
 * @var t_object::material
 * Material properties of the object, including color and reflection.
 *
 * @var t_object::oc
 * Offset vector from the origin to the center of the object.
 *
 * @var t_object::type
 * Enumerated type indicating the specific type of the object.
 *
 * @var t_object::next
 * Pointer to the next object in the linked list.
 *
 * @var t_object::local
 * Axis information for local coordinate transformations.
 *
 * Use this struct to define and manage various objects in a 3D environment.
 */
typedef struct s_object
{
	union
	{
		t_plane		*plane;
		t_sphere	*sphere;
		t_cylinder	*cylinder;
		t_cone		*cone;
		t_light		*spot;
	};
	t_img			texture;
	bool			checkerboard;
	t_material		material;
	t_vector		oc;
	enum e_type		type;
	struct s_object	*next;
	t_axis			local;
}	t_object;

/**
 * @struct t_scene
 * @brief Represents a scene in a 3D environment.
 *
 * This structure encapsulates the elements of a 3D scene, including the
 * active camera, ambient light, lights, and objects (spheres, planes, etc.).
 *
 * @var t_scene::camera
 * Pointer to the active camera in the scene.
 *
 * @var t_scene::ambient
 * Pointer to the ambient light in the scene.
 *
 * @var t_scene::light
 * Pointer to the lights in the scene.
 *
 * @var t_scene::spots
 * Pointer to the list of light source objects in the scene.
 *
 * @var t_scene::objs
 * Pointer to the list of other objects in the scene (planes, spheres, etc.).
 *
 * Use this struct to define and manage a complete 3D scene.
 */
typedef struct s_scene {
	t_camera		*camera;
	t_ambient_light	*ambient;
	t_light			*light;
	t_object		*spots;
	t_object		*objs;
}	t_scene;

/**
 * @struct t_spots
 * @brief Represents a multi-spotlight in a 3D scene.
 *
 * This structure encapsulates the properties of a multi-spotlight, 
 * including its
 * position, direction, ratio, and color.
 *
 * @var t_spots::position
 * The position of the multi-spotlight.
 *
 * @var t_spots::direction
 * The direction in which the multi-spotlight is pointing.
 *
 * @var t_spots::ratio
 * The brightness ratio of the multi-spotlight.
 *
 * @var t_spots::color
 * The color of the multi-spotlight.
 *
 * Use this struct to define and manage multi-spotlight properties 
 * in a 3D environment.
 */
typedef struct s_spots {
	t_vector	position;
	t_vector	direction;
	double		ratio;
	t_color		color;
}	t_spots;

/**
 * @brief Calculate the intersection distance of a ray with a cylinder.
 * and set the (t_hit) hit struct
 * @param ray   Pointer to the ray structure.
 * @param objs  Pointer to the object representing the cylinder.
 * @return      The distance to the closest intersection point
 * or INFINITY if no intersection.
 */
double	cylinder_int(t_ray *ray, t_object *objs);

/**
 * @brief Calculate the intensity of light along a ray from a light source.
 * and set the (t_hit) hit struct
 * @param ray    Pointer to the ray structure.
 * @param light  Pointer to the light source.
 * @return       The distance to the closest intersection point
 * or INFINITY if no intersection.
 */
double	light_int(t_ray *ray, t_light *light);

/**
 * @brief Calculate the intersection distance of a ray with a plane.
 * and set the (t_hit) hit struct
 * @param ray   Pointer to the ray structure.
 * @param objs  Pointer to the object representing the plane.
 * @return      The distance to the closest intersection point
 * or INFINITY if no intersection.
 */
double	plane_int(t_ray *ray, t_object *objs);

/**
 * @brief Calculate the intersection distance of a ray with a sphere.
 * and set the (t_hit) hit struct
 * @param ray   Pointer to the ray structure.
 * @param objs  Pointer to the object representing the sphere.
 * @return      The distance to the closest intersection point
 * or INFINITY if no intersection.
 */
double	sphere_int(t_ray *ray, t_object *objs);

/**
 * @brief Calculate the intersection distance of a ray with a cone.
 * and set the (t_hit) hit struct
 * @param ray   Pointer to the ray structure.
 * @param objs  Pointer to the object representing the cone.
 * @return      The distance to the closest intersection point
 * or INFINITY if no intersection.
 */
double	cone_int(t_ray *ray, t_object *objs);

#endif