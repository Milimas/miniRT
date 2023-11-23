/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:21:58 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/11/23 17:28:00 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_TITLE "miniRT"

# define ELIPS 1e-3

# if LINUX
#  define K_ESCAPE				65307
# else
#  define K_ESCAPE               0x35
# endif

# include "window.h"
# include "vector.h"
# include "color.h"
# include "../libft/libft.h"
# include "image.h"
# include "ray.h"
# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include "parsing.h"
# include "lighting.h"
# include "matrix.h"

/**
 * @brief Solve a quadratic equation and store the results in a quadratic 
 * structure.
 *
 * @param res Pointer to the quadratic structure to store the results.
 * @param t The discriminant value.
 */
void		solve_quadratic(t_quadratic *res, double t);

/**
 * @brief Clamp a value within a specified range.
 *
 * @param value The value to clamp.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 * @return The clamped value.
 */
double		clamp(double value, double min, double max);

/**
 * @brief Get the maximum of two values.
 *
 * @param a The first value.
 * @param b The second value.
 * @return The maximum of the two values.
 */
double		max(double min, double max);

/**
 * @brief Apply sphere mapping to a ray.
 *
 * @param ray Pointer to the ray structure.
 */
void		sphere_map(t_ray *ray);

/**
 * @brief Apply cylinder mapping to a ray with a given distance.
 *
 * @param ray Pointer to the ray structure.
 * @param dist The distance for mapping.
 */
void		cylinder_map(t_ray *ray, double dist);

/**
 * @brief Apply plane mapping to a ray.
 *
 * @param ray Pointer to the ray structure.
 */
void		plane_map(t_ray *ray);

/**
 * @brief Apply cone mapping to a ray with a given distance.
 *
 * @param ray Pointer to the ray structure.
 * @param dist The distance for mapping.
 */
void		cone_map(t_ray *ray, double dist);

/**
 * @brief Apply checkerboard pattern to a ray.
 *
 * @param ray Pointer to the ray structure.
 */

void		checkerboard(t_ray *ray);

/**
 * @brief Apply texture to a ray.
 *
 * @param ray Pointer to the ray structure.
 */
void		texture(t_ray *ray);

/**
 * @brief Apply bump mapping texture to a ray.
 *
 * @param ray Pointer to the ray structure.
 */
void		bump_map_texture(t_ray *ray);

/**
 * @brief Close the graphics rendering window.
 *
 * @param mlx Pointer to the mlx structure.
 * @return 0 on success, -1 on failure.
 */

int			close_window(t_mlx *mlx);

/**
 * @brief Initialize the graphics rendering window.
 *
 * @param window Pointer to the window structure.
 */
void		init_window(t_window *window);

/**
 * @brief Render the graphics in the window.
 *
 * @param window Pointer to the window structure.
 * @return 0 on success.
 */
int			render(t_window *window);

/**
 * @brief Find intersections in the scene for a given ray and update the window.
 *
 * @param ray    Pointer to the ray structure.
 * @param window Pointer to the window structure.
 */
void		intersect(t_ray *ray, t_window *window);

/**
 * @brief Create a new camera with default parameters.
 *
 * @param cam Pointer to the camera structure.
 * @return Pointer to the created camera.
 */
t_camera	*create_camera(t_camera *cam);

/**
 * @brief Calculate the local axis based on the given forward vector.
 *
 * @param forward The forward vector.
 * @return The calculated local axis.
 */
t_axis		local_axis(t_vector forward);

/**
 * @brief Print the components of a vector to the console.
 *
 * @param str String to display before the vector components.
 * @param v   Vector to be printed.
 */
void		print_vector(char *str, t_vector v);

/**
 * @brief Print the information about the scene to the console.
 *
 * @param window The window structure containing the scene.
 */
void		print_scene(t_window window);

/**
 * @brief Print the properties of a cylinder to the console.
 *
 * @param c Pointer to the cylinder structure.
 */
void		print_cylinder(t_cylinder *c);

/**
 * @brief Print the properties of a camera to the console.
 *
 * @param cam Pointer to the camera structure.
 */
void		print_camera(t_camera *cam);

/**
 * @brief Print the properties of a plane to the console.
 *
 * @param p Pointer to the plane structure.
 */
void		print_plane(t_plane *p);

/**
 * @brief Print the properties of a sphere to the console.
 *
 * @param s Pointer to the sphere structure.
 */
void		print_sphere(t_sphere *s);

#endif
