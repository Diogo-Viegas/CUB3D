/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gocaetan <gocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:41:43 by gocaetan          #+#    #+#             */
/*   Updated: 2026/04/21 12:47:27 by gocaetan         ###   ########.fr       */
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
