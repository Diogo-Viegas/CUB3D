/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dviegas <dviegas@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:58:14 by gocaetan          #+#    #+#             */
/*   Updated: 2026/05/12 12:11:16 by dviegas          ###   ########.fr       */
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

void	door_colision(t_game *game, t_ray *ray)
{
	if (game->map.grid[ray->map_y][ray->map_x] == 'D')
	{
		if (!is_door_open(game, ray->map_x, ray->map_y))
		{
			ray->door = 1;
			ray->hit = 1;
		}
	}
}

void	clear_img(int width, int height, t_img *img)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			put_pixel(img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}
