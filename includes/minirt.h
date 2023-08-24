/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:21:58 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/08/24 22:32:37 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_TITLE "miniRT"

# ifdef __linux
#  include <mlx.h>
# elif __APPLE__
#  include "mlx/mlx.h"
# endif

# include "vector.h"
# include "color.h"
# include "../libft/libft.h"
# include "image.h"
# include <math.h>

/**
 * @struct s_img
 * @brief Represents an image for graphics rendering.
 *
 * This struct encapsulates properties of an image, such as its pointer,
 * address, bits per pixel, size per line, and endianness.
 *
 * @var s_img::img_ptr
 * Pointer to the image.
 * 
 * @var s_img::addr
 * Address of the image.
 * 
 * @var s_img::bits_per_pixel
 * Number of bits per pixel.
 * 
 * @var s_img::size_line
 * Size per line of the image.
 * 
 * @var s_img::endian
 * Endianness of the image.
 *
 * Use this struct to manage image properties in graphics rendering.
 */
typedef struct s_img {
	void	*img_ptr;
	int		*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_img;

/**
 * @struct t_mlx
 * @brief Represents a connection to the MiniLibX library.
 *
 * This structure encapsulates the properties of a MiniLibX connection,
 * including pointers to the library and window.
 *
 * @var t_mlx::mlx_ptr
 * Pointer to the MiniLibX library.
 *
 * @var t_mlx::win_ptr
 * Pointer to the window.
 *
 * Use this structure to manage the connection and window when utilizing
 * the MiniLibX library for graphics rendering.
 */
typedef struct s_mlx {
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx;

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
	t_list	*cameras;
	t_list	*lights;
	t_list	*planes;
	t_list	*triangles;
	t_list	*spheres;
	t_list	*squares;
	t_list	*cylinders;
}	t_scene;

/**
 * @struct s_window
 * @brief Represents a graphics rendering window.
 *
 * This struct encapsulates elements of a graphics window, including a
 * pointer to MiniLibX connection (t_mlx) and an image (t_img) for rendering.
 *
 * @var s_window::mlx
 * Pointer to the MiniLibX connection.
 * 
 * @var s_window::img
 * Image for rendering graphics.
 * 
 * @var s_window::scene
 * Scene data associated with the window.
 *
 * Use this struct to define and manage a graphics rendering window.
 */
typedef struct s_window {
	t_mlx	mlx;
	t_img	img;
	t_scene	scene;
}	t_window;

/**
 * @brief Creates a 32-bit color value from individual color components.
 *
 * This function combines the transparency (t), red (r), green (g), and blue (b)
 * color components into a single 32-bit color value.
 *
 * @param t Transparency value (0-255).
 * @param r Red color value (0-255).
 * @param g Green color value (0-255).
 * @param b Blue color value (0-255).
 * @return The combined 32-bit color value.
 */
int		create_trgb(int t, int r, int g, int b);

/**
 * @brief Sets a pixel's color in the given image.
 *
 * This function modifies the color of a pixel in the specified image (img)
 * at the specified position (pixel) to the provided color value.
 *
 * @param img Pointer to the image where the pixel color will be changed.
 * @param pixel Coordinates of the pixel to be modified.
 * @param color Color value to be applied to the pixel.
 */
void	put_pixel(t_img *img, t_pixel pixel, int color);

#endif
