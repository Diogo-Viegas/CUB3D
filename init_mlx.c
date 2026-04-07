#include "cub3d.h"

int	close_game(t_game *game)
{
	clean_all(game);
	exit(0);
}

int	esc_close(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_game(game);
	return (0);
}

void	init_mlx(t_game *game)
{
	game->win_width = 1280;
	game->win_height = 720;
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		clean_all(game);
		error_exit("mlx_init() failed");
	}
	game->win = mlx_new_window(game->mlx, game->win_width, game->win_height,
			"Cub3D");
	if (!game->win)
	{
		clean_all(game);
		error_exit("Failed to create MLX window");
	}
	game->screen.img_ptr = mlx_new_image(game->mlx, game->win_width,
			game->win_height);
	if (!game->screen.img_ptr)
	{
		clean_all(game);
		error_exit("Failed to create screen image");
	}
	game->screen.addr = mlx_get_data_addr(game->screen.img_ptr,
			&game->screen.bpp, &game->screen.line_len, &game->screen.endian);
	if (!game->screen.addr)
	{
		clean_all(game);
		error_exit("Failed to get data address");
	}
	game->screen.width = game->win_width;
	game->screen.height = game->win_height;
}
