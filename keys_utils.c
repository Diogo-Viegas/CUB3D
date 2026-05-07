/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dviegas <dviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:41:43 by gocaetan          #+#    #+#             */
/*   Updated: 2026/05/07 11:56:31 by dviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(angle) - game->player.dir_y
		* sin(angle);
	game->player.dir_y = old_dir_x * sin(angle) + game->player.dir_y
		* cos(angle);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle) + game->player.plane_y
		* cos(angle);
}

void	rotate_right(t_game *game, double angle)
{
	rotate_left(game, -angle);
}

int	mouse_move_hook(int x, int y, t_game *game)
{
	int		center_x;
	int		delta_x;
	double	sensibility;

	(void)y;
	if (!game->mouse_enabled)
		return (0);
	center_x = game->win_width / 2;
	delta_x = x - center_x;
	sensibility = -0.002;
	if (delta_x > 0)
		rotate_right(game, delta_x * sensibility);
	else if (delta_x < 0)
		rotate_left(game, -delta_x * sensibility);
	mlx_mouse_move(game->mlx, game->win, center_x, game->win_height / 2);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 119)
		game->keys.w = 0;
	if (keycode == 115)
		game->keys.s = 0;
	if (keycode == 65361)
		game->keys.left = 0;
	if (keycode == 65363)
		game->keys.right = 0;
	if (keycode == 97)
		game->keys.a = 0;
	if (keycode == 100)
		game->keys.d = 0;
	return (0);
}
