#include "cub3d.h"

void	render_map(t_game *game)
{
	int	y;
	int	x;
	int	pos[2];
	int	color;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			pos[0] = MINIMAP_OFFSET_X + x * MINIMAP_SCALE;
			pos[1] = MINIMAP_OFFSET_Y + y * MINIMAP_SCALE;
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
	int	start[2];
	int	end[2];

	start[0] = MINIMAP_OFFSET_X + game->player.x * MINIMAP_SCALE;
	start[1] = MINIMAP_OFFSET_Y + game->player.y * MINIMAP_SCALE;
	end[0] = start[0] + game->player.dir_x * 15;
	end[1] = start[1] + game->player.dir_y * 15;
	draw_line(&game->screen, start, end, 0xFF0000);
}

void	render_player(t_game *game)
{
	int	pos[2];

	pos[0] = MINIMAP_OFFSET_X + game->player.x * MINIMAP_SCALE;
	pos[1] = MINIMAP_OFFSET_Y + game->player.y * MINIMAP_SCALE;
	draw_square(&game->screen, pos, 4, 0xFF0000);
}
void	draw_ray_minimap(t_img *img, t_player *player, t_ray *ray)
{
	int	start[2];
	int	end[2];

	start[0] = MINIMAP_OFFSET_X + player->x * MINIMAP_SCALE;
	start[1] = MINIMAP_OFFSET_Y + player->y * MINIMAP_SCALE;
	end[0] = MINIMAP_OFFSET_X + (player->x + ray->ray_dir_x * ray->wall_dist)
		* MINIMAP_SCALE;
	end[1] = MINIMAP_OFFSET_Y + (player->y + ray->ray_dir_y * ray->wall_dist)
		* MINIMAP_SCALE;
	draw_line(img, start, end, 0x00FF00);
}

void	render_minimap_rays(t_game *game)
{
	t_ray ray;
	int x;

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