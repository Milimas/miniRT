/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:21:58 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/19 22:23:59 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_WIDTH 500
# define WIN_HEIGHT 500
# define WIN_TITLE "miniRT"

# ifdef __linux
#  include <mlx.h>
# elif __APPLE__
#  include "mlx/mlx.h"
# endif

# include "vector.h"
# include "color.h"
# include "../libft/libft.h"

/*
 * Structure representing an image.
 *
 * This struct encapsulates the properties of an image, including its pointer,
 * address, bits per pixel, size per line, and endianness.
 *
 * Members:
 * - img_ptr: Pointer to the image.
 * - addr: Address of the image.
 * - bits_per_pixel: Number of bits per pixel.
 * - size_line: Size per line of the image.
 * - endian: Endianness of the image.
 *
 * Use this struct to define and manage image properties.
 */
typedef struct s_img {
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_img;

/*
 * Structure representing a connection to the MiniLibX library.
 *
 * This struct encapsulates the properties of a MiniLibX connection,
 * including pointers to the library and window.
 *
 * Members:
 * - mlx_ptr: Pointer to the MiniLibX library.
 * - win_ptr: Pointer to the window.
 *
 * Use this struct to manage the connection and window when utilizing
 * the MiniLibX library for graphics rendering.
 */
typedef struct s_mlx {
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx;

/*
 * Structure representing a scene in a 3D environment.
 *
 * This struct encapsulates the elements of a 3D scene, including lists of
 * cameras, lights, planes, triangles, spheres, squares, and cylinders.
 *
 * Members:
 * - cameras: List of cameras in the scene.
 * - lights: List of lights in the scene.
 * - planes: List of planes in the scene.
 * - triangles: List of triangles in the scene.
 * - spheres: List of spheres in the scene.
 * - squares: List of squares in the scene.
 * - cylinders: List of cylinders in the scene.
 *
 * Use this struct to define and manage a complete 3D scene.
 */
typedef struct s_scene {
	t_list	*cameras;
	t_list	*lights;
	t_list	*planes;
	t_list	*triangles;
	t_list	*spheres;
	t_list	*squares;
	t_list	*cylinders;
}	t_scene;

/*
 * Structure representing a window for graphics rendering.
 *
 * This struct encapsulates the elements of a graphics window, including a
 * pointer to the MiniLibX connection (t_mlx) and an image (t_img) for rendering.
 *
 * Members:
 * - mlx: Pointer to the MiniLibX connection.
 * - img: Image for rendering graphics.
 *
 * Use this struct to define and manage a graphics rendering window.
 */
typedef struct s_window {
	t_mlx	*mlx;
	t_img	img;
}	t_window;

int		create_trgb(int t, int r, int g, int b);
void	put_pixel(t_img *img, int x, int y, int color);

#endif
