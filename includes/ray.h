#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "color.h"

typedef	struct s_object t_object;

enum e_type
{
	NONE,
	CAMERA,
	PLANE,
	SPHERE,
	CYLINDER,
	POINT_LIGHT,
	AMBIENT_LIGHT,
};

typedef struct s_hit
{
	t_vector	at;
	double		t;
	t_vector	normal;
	t_color		color;
	t_object	*obj;
	enum e_type	type;
}	t_hit;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	dir;
	t_hit		hit;
	double		illumination;
	int			not_shadow;
}	t_ray;

#endif