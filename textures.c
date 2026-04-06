#include "cub3d.h"

//em que sitio da parede o raio bateu?
void calc_wall_x(t_game *game, t_ray *ray)
{
    if(ray->side == 0)
        ray->wallx = game->player.y + ray->perpWallDist * ray->rayDirY;
    else 
        ray->wallx =game->player.x + ray->perpWallDist * ray->rayDirX;
    ray->wallx -= floor(ray->wallx);
}
t_img *get_wall_texture(t_game *game, t_ray *ray)
{
    if(ray->side == 0)
    {
        if(ray->rayDirX > 0)
            return (&game->texture_ea);
        else
            return (&game->texture_we);
    }
    else
    {
        if(ray->rayDirY > 0)
            return (&game->texture_so);
        else
            return(&game->texture_no);
    }
}

void calc_texture_x(t_ray *ray, t_img *texture)
{
    ray->texX = (int)(ray->wallx * (double)texture->width);
    if (ray->texX < 0)
	    ray->texX = 0;
    if (ray->texX >= texture->width)
	    ray->texX = texture->width - 1;
    if(ray->side == 0 && ray->rayDirX > 0)
        ray->texX = texture->width - ray->texX - 1;
    if(ray->side == 1 && ray->rayDirY < 0)
        ray->texX = texture->width - ray->texX - 1;
}
int get_texture_pixel(t_img *img,int x,int y)
{
    char *dst;
    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    return(*(unsigned int *)dst);
}
void draw_textured_column(t_game *game, int x, t_ray *ray, t_img *texture)
{
	int		y;
	int		texY;
	int		color;

	y = 0;
	while (y < ray->drawStart)
	{
		put_pixel(&game->screen, x, y, game->map.ceiling);
		y++;
	}
	ray->step = (double)texture->height / ray->lineHeight;
	ray->texPos = (ray->drawStart - game->win_height / 2
			+ ray->lineHeight / 2) * ray->step;
	while (y <= ray->drawEnd)
	{
		texY = (int)ray->texPos;
		if (texY < 0)
			texY = 0;
		if (texY >= texture->height)
			texY = texture->height - 1;
		color = get_texture_pixel(texture, ray->texX, texY);
		put_pixel(&game->screen, x, y, color);
		ray->texPos += ray->step;
		y++;
	}
	while (y < game->win_height)
	{
		put_pixel(&game->screen, x, y, game->map.floor);
		y++;
	}
}

void	load_texture(t_game *game, t_img *tex, char *path)
{
	tex->img_ptr = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img_ptr)
	{
		printf("Error loading texture: %s\n", path);
		exit(1);
	}
	tex->addr = mlx_get_data_addr(tex->img_ptr,
			&tex->bpp, &tex->line_len, &tex->endian);
	if (!tex->addr)
	{
		printf("Error getting texture addr\n");
		exit(1);
	}
}
void	init_textures(t_game *game)
{
	load_texture(game, &game->texture_no, game->map.no);
	load_texture(game, &game->texture_so, game->map.so);
	load_texture(game, &game->texture_ea, game->map.ea);
	load_texture(game, &game->texture_we, game->map.we);
    printf("North: %p addr:%p w:%d h:%d\n",
	game->texture_no.img_ptr,
	game->texture_no.addr,
	game->texture_no.width,
	game->texture_no.height);
}