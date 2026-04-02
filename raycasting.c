#include "cub3d.h"
void init_ray(t_ray *ray, t_player *player, int x, t_map *map)
{
	ray->cameraX = 2 * x / (double)map->width -1;
	ray->rayDirX = player->dir_x + player->plane_x * ray->cameraX;
	ray->rayDirY = player->dir_y + player->plane_y * ray->cameraX;
	ray->mapX = (int)player->x;
	ray->mapY = (int)player->y;
	ray->deltaDistX = fabs(1 / ray->rayDirX);
	ray->deltaDistY = fabs(1 / ray->rayDirY);
	ray->hit = 0;
}
void clear_img(int width, int height, t_img *img)
{
	for(int y = 0; y < width; y++)
		for(int x = 0; x < height; x++)
			put_pixel(img, x, y, 0x000000);
}

void init_dda(t_ray *ray, t_player *player)
{
	if(ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (player->x - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - player->x) * ray->deltaDistX;
	}
	if(ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (player->y - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - player->y) * ray->deltaDistY;
	}
}

void perform_dda(t_ray *ray, char **map)
{
	while(ray->hit == 0)
	{
		if (ray->mapX < 0 || ray->mapY < 0 || map[ray->mapY] == NULL || map[ray->mapY][ray->mapX] == '\0')
			break;
		if(ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if(map[ray->mapY][ray->mapX] == '1')
			ray->hit = 1;
	}
}
void calc_dist(t_ray *ray)
{
	if(ray->side == 0)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
}

void draw_ray(t_img *img, t_player *player, t_ray *ray)
{
	int startX = player->x * TILE_SIZE;
	int startY = player->y * TILE_SIZE;

	int endX = (player->x + ray->rayDirX * ray->perpWallDist) * TILE_SIZE;
	int endY = (player->y + ray->rayDirY * ray->perpWallDist) * TILE_SIZE;
	draw_line(img, startX, startY, endX, endY, 0x00FF00);
}
void	cast_rays(t_game *game)
{
	t_ray	ray;

	for (int x = 0; x < 10; x++)
	{
		init_ray(&ray, &game->player, x, &game->map);
		init_dda(&ray, &game->player);
		perform_dda(&ray, game->map.grid);
		calc_dist(&ray);
		draw_ray(&game->screen, &game->player, &ray);
	}
}
void draw_line(t_img *img, int x0, int y0, int x1, int y1, int color)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float x_inc = dx / (float)steps;
    float y_inc = dy / (float)steps;

    float x = x0;
    float y = y0;

    for (int i = 0; i <= steps; i++)
    {
        put_pixel(img, (int)x, (int)y, color);
        x += x_inc;
        y += y_inc;
    }
}