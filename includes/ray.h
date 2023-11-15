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
	CONE,
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

#endif