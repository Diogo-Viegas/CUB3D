#include "cub3d.h"

void render_map(t_game *game)
{
    int y;
    int x;
    int screen_y;
    int screen_x;
    int color;

    y = 0;
    while (y < game->map.height)
    {
        x = 0;
	while (x < game->map.width)
		{
			screen_x = MINIMAP_OFFSET_X + x * MINIMAP_SCALE;
			screen_y = MINIMAP_OFFSET_Y + y * MINIMAP_SCALE;
			if (game->map.grid[y][x] == '1')
				color = 0xFFFFFF;
			else
				color = 0x222222;
			draw_square(&game->screen, screen_x, screen_y, MINIMAP_SCALE, color);
			x++;
		}
		y++;
    }
}

void	render_player_direction(t_game *game)
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;

	start_x = MINIMAP_OFFSET_X + game->player.x * MINIMAP_SCALE;
	start_y = MINIMAP_OFFSET_Y + game->player.y * MINIMAP_SCALE;
	end_x = start_x + game->player.dir_x * 15;
	end_y = start_y + game->player.dir_y * 15;
	draw_line(&game->screen, start_x, start_y, end_x, end_y, 0xFF0000);
}

void	render_player(t_game *game)
{
	int	px;
	int	py;
    px = MINIMAP_OFFSET_X + game->player.x * MINIMAP_SCALE;
	py = MINIMAP_OFFSET_Y + game->player.y * MINIMAP_SCALE;
	draw_square(&game->screen, px - 2, py - 2, 4, 0xFF0000);
}
void	draw_ray_minimap(t_img *img, t_player *player, t_ray *ray)
{
	int	startX;
	int	startY;
	int	endX;
	int	endY;

	startX = MINIMAP_OFFSET_X + player->x * MINIMAP_SCALE;
	startY = MINIMAP_OFFSET_Y + player->y * MINIMAP_SCALE;

	endX = MINIMAP_OFFSET_X + (player->x + ray->rayDirX * ray->perpWallDist) * MINIMAP_SCALE;
	endY = MINIMAP_OFFSET_Y + (player->y + ray->rayDirY * ray->perpWallDist) * MINIMAP_SCALE;

	draw_line(img, startX, startY, endX, endY, 0x00FF00);
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

		x += 40; // não desenhar todos
	}
}