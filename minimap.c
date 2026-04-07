/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gocaetan <gocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:42:53 by gocaetan          #+#    #+#             */
/*   Updated: 2026/04/07 17:42:54 by gocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	render_player(t_game *game)
{
	t_point	pos;

	pos.x = MINIMAP_OFFSET_X + game->player.x * MINIMAP_SCALE;
	pos.y = MINIMAP_OFFSET_Y + game->player.y * MINIMAP_SCALE;
	draw_square(&game->screen, pos, 4, 0xFF0000);
}

void	draw_ray_minimap(t_img *img, t_player *player, t_ray *ray)
{
	t_point	start;
	t_point	end;

	start.x = MINIMAP_OFFSET_X + player->x * MINIMAP_SCALE;
	start.y = MINIMAP_OFFSET_Y + player->y * MINIMAP_SCALE;
	end.x = MINIMAP_OFFSET_X + (player->x + ray->ray_dir_x * ray->wall_dist)
		* MINIMAP_SCALE;
	end.y = MINIMAP_OFFSET_Y + (player->y + ray->ray_dir_y * ray->wall_dist)
		* MINIMAP_SCALE;
	draw_line(img, start, end, 0x00FF00);
}

void	render_minimap_rays(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < game->win_width)
	{
		init_ray(&ray, game, x);
		init_dda(&ray, &game->player);
		perform_dda(&ray, game);
		calc_dist(&ray);
		draw_ray_minimap(&game->screen, &game->player, &ray);
		x += 40;
	}
}
