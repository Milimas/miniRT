#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "color.h"

typedef	struct s_object t_object;

typedef struct s_hit
{
	t_vector	at;
	double		t;
	t_vector	normal;
	t_trgb		color;
	t_object	*obj;
}	t_hit;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	dir;
	t_hit		hit;
}	t_ray;

#endif