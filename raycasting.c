#include "cub3d.h"

void	init_ray(t_ray *ray, t_game *game, int x)
{
	ray->camera_x = 2 * x / (double)game->win_width - 1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
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

void	init_dda(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->y) * ray->delta_dist_y;
	}
}

void	perform_dda(t_ray *ray, t_game *game)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_y >= game->map.height || ray->map_x < 0
			|| ray->map_x >= game->map.width)
		{
			ray->hit = 1;
			return ;
		}
		if (game->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}
void	calc_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->wall_dist = (ray->side_dist_y - ray->delta_dist_y);
}

void	draw_ray(t_img *img, t_player *player, t_ray *ray)
{
	int	start[2];
	int	end[2];

	start[0] = player->x * TILE_SIZE;
	start[1] = player->y * TILE_SIZE;
	end[0] = (player->x + ray->ray_dir_x * ray->wall_dist) * TILE_SIZE;
	end[1] = (player->y + ray->ray_dir_y * ray->wall_dist) * TILE_SIZE;
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
		// color = 0x00FF00;
		// if(ray.side == 1)
		//	color = 0x008800;
		// draw_vertical_line(game,x,draw_start,draw_end,color);
		// draw_ray(&game->screen, &game->player, &ray);
		texture = get_wall_texture(game, &ray);
		calc_texture_x(&ray, texture);
		draw_textured_column(game, x, &ray, texture);
		x++;
	}
}
void	draw_line(t_img *img, int start[2], int end[2], int color)
{
	int dx = end[0] - start[0];
	int dy = end[1] - start[1];
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	float x_inc = dx / (float)steps;
	float y_inc = dy / (float)steps;

	float x = start[0];
	float y = start[1];

	for (int i = 0; i <= steps; i++)
	{
		put_pixel(img, (int)x, (int)y, color);
		x += x_inc;
		y += y_inc;
	}
}