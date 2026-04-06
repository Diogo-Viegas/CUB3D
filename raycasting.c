#include "cub3d.h"
void init_ray(t_ray *ray, t_game *game,int x)
{
	ray->cameraX = 2 * x / (double)game->win_width -1;
	ray->rayDirX = game->player.dir_x + game->player.plane_x * ray->cameraX;
	ray->rayDirY = game->player.dir_y + game->player.plane_y * ray->cameraX;
	ray->mapX = (int)game->player.x;
	ray->mapY = (int)game->player.y;
	if(ray->rayDirX == 0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX =  fabs(1 / ray->rayDirX);
	if(ray->rayDirY == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY =  fabs(1 / ray->rayDirY);
	ray->hit = 0;
}
void clear_img(int width, int height, t_img *img)
{
	int y;
	int x;

	y = 0;
	while(y < height)
	{
		x = 0;
		while(x < width)
		{
			put_pixel(img, x, y, 0x000000);
			x++;
		}
		y++;
	}
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

void	perform_dda(t_ray *ray, t_game *game)
{
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
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
		if (ray->mapY < 0 || ray->mapY >= game->map.height
			|| ray->mapX < 0 || ray->mapX >= game->map.width)
		{
			ray->hit = 1;
			return ;
		}
		if (game->map.grid[ray->mapY][ray->mapX] == '1')
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
	int startX;
	int startY;
	int endX;
	int endY;

	startX = player->x * TILE_SIZE;
	startY = player->y * TILE_SIZE;
	endX = (player->x + ray->rayDirX * ray->perpWallDist) * TILE_SIZE;
	endY = (player->y + ray->rayDirY * ray->perpWallDist) * TILE_SIZE;
	draw_line(img,startX,startY,endX,endY,0x00FF00);

}
void	cast_rays(t_game *game)
{
	t_ray	ray;
	t_img  *texture;
	int x;

	x = 0;
	while(x < game->win_width)
	{
		init_ray(&ray,game,x);
		init_dda(&ray, &game->player);
		perform_dda(&ray, game);
		calc_dist(&ray);
		calc_wall_height(game,&ray);
		calc_wall_x(game,&ray);
		//color = 0x00FF00;
		//if(ray.side == 1)
		//	color = 0x008800;
		//draw_vertical_line(game,x,drawStart,drawEnd,color);
		//draw_ray(&game->screen, &game->player, &ray);
		texture = get_wall_texture(game, &ray);
		calc_texture_x(&ray,texture);
		draw_textured_column(game,x,&ray,texture);
		x++;
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