#include "includes/minirt.h"
#include <mlx.h>

int main()
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);

	mlx_loop(mlx);
}
