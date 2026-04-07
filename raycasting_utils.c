/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gocaetan <gocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:58:14 by gocaetan          #+#    #+#             */
/*   Updated: 2026/04/07 17:58:31 by gocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ray(t_img *img, t_player *player, t_ray *ray)
{
	t_point	start;
	t_point	end;

	start.x = player->x * TILE_SIZE;
	start.y = player->y * TILE_SIZE;
	end.x = (player->x + ray->ray_dir_x * ray->wall_dist) * TILE_SIZE;
	end.y = (player->y + ray->ray_dir_y * ray->wall_dist) * TILE_SIZE;
	draw_line(img, start, end, 0x00FF00);
}

void	cast_rays(t_game *game)
{
	t_ray	ray;
	t_img	*texture;
	int		x;

	x = 0;
	while (x < game->win_width)
	{
		init_ray(&ray, game, x);
		init_dda(&ray, &game->player);
		perform_dda(&ray, game);
		calc_dist(&ray);
		calc_wall_height(game, &ray);
		calc_wall_x(game, &ray);
		texture = get_wall_texture(game, &ray);
		calc_texture_x(&ray, texture);
		draw_textured_column(game, x, &ray, texture);
		x++;
	}
}

static void	init_line(t_point start, t_point end, t_line *line)
{
	int	dx;
	int	dy;

	dx = end.x - start.x;
	dy = end.y - start.y;
	if (abs(dx) > abs(dy))
		line->steps = abs(dx);
	else
		line->steps = abs(dy);
	line->x_inc = dx / (float)line->steps;
	line->y_inc = dy / (float)line->steps;
	line->x = start.x;
	line->y = start.y;
}

void	draw_line(t_img *img, t_point start, t_point end, int color)
{
	t_line	line;
	int		i;

	init_line(start, end, &line);
	i = 0;
	while (i <= line.steps)
	{
		put_pixel(img, (int)line.x, (int)line.y, color);
		line.x += line.x_inc;
		line.y += line.y_inc;
		i++;
	}
}
