/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:21:58 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/11/23 15:40:28 by aminebeihaq      ###   ########.fr       */
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

// options
# define CHECKER

// math
void		solve_quadratic(t_quadratic *res, double t);
double		clamp(double value, double min, double max);
double		max(double min, double max);

// checker_map
void		sphere_map(t_ray *ray);
void		cylinder_map(t_ray *ray, double dist);
void		plane_map(t_ray *ray);
void		cone_map(t_ray *ray, double dist);
void		checkerboard(t_ray *ray);
void		texture(t_ray *ray);
void		bump_map_texture(t_ray *ray);

void		print_vector(char *str, t_vector v);
int			render(t_window *window);

// window
int			close_window(t_mlx *mlx);
void		init_window(t_window *window);

void		intersect(t_ray *ray, t_window *window);
t_camera	*create_camera(t_camera *cam);
t_axis		local_axis(t_vector forward);

// debug
void		print_vector(char *str, t_vector v);
void		print_scene(t_window window);
void		print_cylinder(t_cylinder *c);
void		print_camera(t_camera *cam);
void		print_plane(t_plane *p);
void		print_sphere(t_sphere *s);

#endif
