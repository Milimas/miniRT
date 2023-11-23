/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:26:01 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/11/23 13:26:10 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "elements.h"
# include <math.h>

typedef struct s_object	t_object;
typedef struct s_camera	t_camera;

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

typedef struct s_ray
{
	t_vector	origin;
	t_vector	dir;
	t_hit		hit;
	t_pixel		p;
	double		aspec;
}	t_ray;

t_ray		generate_ray(t_pixel p, t_camera *cam);
t_vector	at(t_ray ray, double t);

#endif