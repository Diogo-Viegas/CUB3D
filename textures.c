/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gocaetan <gocaetan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:02:08 by dviegas           #+#    #+#             */
/*   Updated: 2026/04/21 12:48:15 by gocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// em que sitio da parede o raio bateu?
void	calc_wall_x(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->wallx = game->player.y + ray->wall_dist * ray->ray_dir_y;
	else
		ray->wallx = game->player.x + ray->wall_dist * ray->ray_dir_x;
	ray->wallx -= floor(ray->wallx);
}

t_img	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->door == 1)
		return (&game->door_texture);
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&game->texture_ea);
		else
			return (&game->texture_we);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (&game->texture_so);
		else
			return (&game->texture_no);
	}
}

void	calc_texture_x(t_ray *ray, t_img *texture)
{
	ray->tex_x = (int)(ray->wallx * (double)texture->width);
	if (ray->tex_x < 0)
		ray->tex_x = 0;
	if (ray->tex_x >= texture->width)
		ray->tex_x = texture->width - 1;
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = texture->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = texture->width - ray->tex_x - 1;
}

static void	draw_wall(t_game *game, int x, t_ray *ray, t_img *texture)
{
	int	y;
	int	texy;
	int	color;

	y = ray->draw_start;
	ray->step = (double)texture->height / ray->line_height;
	ray->tex_pos = (ray->draw_start - game->win_height / 2 + ray->line_height
			/ 2) * ray->step;
	while (y <= ray->draw_end)
	{
		texy = (int)ray->tex_pos;
		if (texy < 0)
			texy = 0;
		if (texy >= texture->height)
			texy = texture->height - 1;
		color = get_texture_pixel(texture, ray->tex_x, texy);
		put_pixel(&game->screen, x, y, color);
		ray->tex_pos += ray->step;
		y++;
	}
}

// Parti em duas
void	draw_textured_column(t_game *game, int x, t_ray *ray, t_img *texture)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel(&game->screen, x, y, game->map.ceiling);
		y++;
	}
	draw_wall(game, x, ray, texture);
	y = ray->draw_end + 1;
	while (y < game->win_height)
	{
		put_pixel(&game->screen, x, y, game->map.floor);
		y++;
	}
}
