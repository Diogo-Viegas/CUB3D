/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gocaetan <gocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 12:57:16 by gocaetan          #+#    #+#             */
/*   Updated: 2026/04/21 12:58:44 by gocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
