#include "includes/minirt.h"

#ifdef __linux
#include <mlx.h>
#endif
#include "mlx/mlx.h"

int main()
{
	void	*mlx;
	void	*mlx_win;

	(void)mlx_win;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);

	mlx_loop(mlx);
}
