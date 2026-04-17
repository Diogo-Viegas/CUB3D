/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gocaetan <gocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:42:04 by gocaetan          #+#    #+#             */
/*   Updated: 2026/04/17 17:15:50 by gocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_blocked(t_game *game, int x, int y)
{
	char tile;
	tile = game->map.grid[y][x];
	if(tile == '1')
		return(1);
	if(tile == 'D')
		return(1);
	return(0);
}

void	move_right(t_game *game, double speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.dir_y * speed;
	new_y = game->player.y + game->player.dir_x * speed;
	if (!is_blocked(game, (int)new_x, (int)game->player.y))
		game->player.x = new_x;
	if (!is_blocked(game, (int)game->player.x, (int)new_y))
		game->player.y = new_y;
}

void	move_left(t_game *game, double speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_y * speed;
	new_y = game->player.y - game->player.dir_x * speed;
	if (!is_blocked(game, (int)new_x, (int)game->player.y))
		game->player.x = new_x;
	if (!is_blocked(game, (int)game->player.x, (int)new_y))
		game->player.y = new_y;
}

void	move_forward(t_game *game, double speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_x * speed;
	new_y = game->player.y + game->player.dir_y * speed;
	if (!is_blocked(game, (int)new_x, (int)game->player.y))
		game->player.x = new_x;
	if (!is_blocked(game, (int)game->player.x, (int)new_y))
		game->player.y = new_y;
}

void	move_backwards(t_game *game, double speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.dir_x * speed;
	new_y = game->player.y - game->player.dir_y * speed;
	if (!is_blocked(game, (int)new_x, (int)game->player.y))
		game->player.x = new_x;
	if (!is_blocked(game, (int)game->player.x, (int)new_y))
		game->player.y = new_y;
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_game(game);
	if (keycode == 119)
		move_forward(game, 0.1);
	if (keycode == 115)
		move_backwards(game, 0.1);
	if (keycode == 65361)
		rotate_right(game, 0.05);
	if (keycode == 65363)
		rotate_left(game, 0.05);
	if (keycode == 97)
		move_left(game, 0.1);
	if (keycode == 100)
		move_right(game, 0.1);
	return (0);
}
