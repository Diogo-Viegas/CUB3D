/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dviegas <dviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:14:42 by gocaetan          #+#    #+#             */
/*   Updated: 2026/04/13 13:02:15 by dviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// Parti em duas
static void	init_screen(t_game *game)
{
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
	mlx_mouse_move(game->mlx, game->win, game->win_width / 2, game->win_height
		/ 2);
	mlx_hook(game->win, 6, 1L << 6, mouse_move_hook, game);
	init_screen(game);
}
