/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gocaetan <gocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:42:53 by gocaetan          #+#    #+#             */
/*   Updated: 2026/04/21 12:58:27 by gocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	door_color(t_game *game, int x, int y)
{
	int	color;

	if (is_door_open(game, x, y))
		color = 0x00FF00;
	else
		color = 0xFF0000;
	return (color);
}

void	render_map(t_game *game)
{
	int		y;
	int		x;
	t_point	pos;
	int		color;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			pos.x = MINIMAP_OFFSET_X + x * MINIMAP_SCALE;
			pos.y = MINIMAP_OFFSET_Y + y * MINIMAP_SCALE;
			if (game->map.grid[y][x] == '1')
				color = 0xFFFFFF;
			else if (game->map.grid[y][x] == 'D')
				color = door_color(game, x, y);
			else
				color = 0x222222;
			draw_square(&game->screen, pos, MINIMAP_SCALE, color);
			x++;
		}
		y++;
	}
}

void	render_player_direction(t_game *game)
{
	t_point	start;
	t_point	end;

	start.x = MINIMAP_OFFSET_X + game->player.x * MINIMAP_SCALE;
	start.y = MINIMAP_OFFSET_Y + game->player.y * MINIMAP_SCALE;
	end.x = start.x + game->player.dir_x * 15;
	end.y = start.y + game->player.dir_y * 15;
	draw_line(&game->screen, start, end, 0xFF0000);
}
