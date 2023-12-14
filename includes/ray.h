/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi    <abeihaqi@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:26:01 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/11/23 17:33:08 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "elements.h"
# include <math.h>

typedef struct s_object	t_object;
typedef struct s_camera	t_camera;

/**
 * @struct t_hit
 * @brief Represents information about the intersection of a ray with an object.
 *
 * This structure contains data such as the intersection point, distance (t),
 * surface normal, color, object type, and UV coordinates.
 *
 * @var t_hit::at
 * The intersection point in 3D space.
 *
 * @var t_hit::t
 * The distance to the intersection point along the ray.
 *
 * @var t_hit::normal
 * The surface normal at the intersection point.
 *
 * @var t_hit::color
 * The color at the intersection point.
 *
 * @var t_hit::obj
 * Pointer to the intersected object.
 *
 * @var t_hit::type
 * The type of the intersected object.
 *
 * @var t_hit::uv
 * UV coordinates at the intersection point.
 */
typedef struct s_hit
{
	t_vector	at;
	double		t;
	t_vector	normal;
	t_color		color;
	t_object	*obj;
	int			type;
	t_pixel		uv;
}	t_hit;

/**
 * @struct t_ray
 * @brief Represents a ray in 3D space.
 *
 * This structure encapsulates the properties of a ray, including its origin,
 * direction and information about its intersection.
 *
 * @var t_ray::origin
 * The origin point of the ray.
 *
 * @var t_ray::dir
 * The direction vector of the ray.
 *
 * @var t_ray::hit
 * Information about the intersection of the ray with an object.
 */
typedef struct s_ray
{
	t_vector	origin;
	t_vector	dir;
	t_hit		hit;
}	t_ray;

/**
 * @brief Generate a ray from a camera for a given pixel.
 *
 * @param p    The pixel position.
 * @param cam  Pointer to the camera.
 * @return     The generated ray.
 */
t_ray		generate_ray(t_pixel p, t_camera *cam);

/**
 * @brief Calculate the point on the ray at a given distance.
 *
 * @param ray  The ray.
 * @param t    The distance along the ray.
 * @return     The point on the ray at the given distance.
 */
t_vector	at(t_ray ray, double t);

#endif