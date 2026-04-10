/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dviegas <dviegas@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:15:46 by gocaetan          #+#    #+#             */
/*   Updated: 2026/04/10 12:07:13 by dviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
void	draw_vertical_line(t_game *game, int x, int draw_start, int draw_end,
		int color)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		put_pixel(&game->screen, x, y, game->map.ceiling);
		y++;
	}
	while (y <= draw_end)
	{
		put_pixel(&game->screen, x, y, color);
		y++;
	}
	while (y < game->win_height)
	{
		put_pixel(&game->screen, x, y, game->map.floor);
		y++;
	}
}
*/
void	calc_wall_height(t_game *game, t_ray *ray)
{
	if (ray->wall_dist < 1e-6)
		ray->wall_dist = 1e-6;
	ray->line_height = (int)(game->win_height / ray->wall_dist);
	ray->draw_start = -ray->line_height / 2 + game->win_height / 2;
	ray->draw_end = ray->line_height / 2 + game->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= game->win_height)
		ray->draw_end = game->win_height - 1;
}
