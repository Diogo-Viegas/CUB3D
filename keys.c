/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gocaetan <gocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:42:04 by gocaetan          #+#    #+#             */
/*   Updated: 2026/04/21 12:46:59 by gocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_continuous_movement(t_game *game)
{
	if (game->keys.w)
		move_forward(game, 0.03);
	if (game->keys.s)
		move_backwards(game, 0.03);
	if (game->keys.a)
		move_left(game, 0.03);
	if (game->keys.d)
		move_right(game, 0.03);
	if (game->keys.left)
		rotate_right(game, 0.02);
	if (game->keys.right)
		rotate_left(game, 0.02);
}

void	handle_keys(int keycode, t_game *game)
{
	int	x;
	int	y;

	if (keycode == 65307)
		close_game(game);
	if (keycode == 119)
		game->keys.w = 1;
	if (keycode == 115)
		game->keys.s = 1;
	if (keycode == 65361)
		game->keys.left = 1;
	if (keycode == 65363)
		game->keys.right = 1;
	if (keycode == 97)
		game->keys.a = 1;
	if (keycode == 100)
		game->keys.d = 1;
	if (keycode == 101)
	{
		x = (int)(game->player.x + game->player.dir_x);
		y = (int)(game->player.y + game->player.dir_y);
		open_door(game, x, y);
	}
}

int	key_press(int keycode, t_game *game)
{
	handle_keys(keycode, game);
	if (keycode == 65513)
		game->mouse_enabled = !game->mouse_enabled;
	return (0);
}
