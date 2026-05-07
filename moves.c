/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dviegas <dviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 11:36:37 by dviegas           #+#    #+#             */
/*   Updated: 2026/05/07 11:57:37 by dviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
