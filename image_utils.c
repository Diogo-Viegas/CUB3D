#include "cub3d.h"

void put_pixel(t_img *img,int x,int y,int color)
{
    char *dst;
    if(x < 0 || y < 0 || x >= img->width || y >= img->height)
        return;
    dst = img->addr + (y * img->line_len + x * (img->bpp /8));
    *(unsigned int *)dst = color;
}

void draw_square(t_img *img,int start_x,int start_y,int size,int color)
{
    int x;
    int y;

    y = 0;
    while(y < size)
    {
        x = 0;
        while(x < size)
        {
            put_pixel(img,start_x + x,start_y + y,color);
            x++;
        }
        y++;
    }
}
void render_map(t_game *game)
{
    int y;
    int x;

    y = 0;
    while (y < game->map.height)
    {
        x = 0;
        while(x < game->map.width)
        {
            if(game->map.grid[y][x] == '1')
                draw_square(&game->screen,x * TILE_SIZE, y * TILE_SIZE,TILE_SIZE,0x00080);
        
            else if(game->map.grid[y][x] == '0')
                draw_square(&game->screen,x * TILE_SIZE,y * TILE_SIZE,TILE_SIZE,0xff00ff);
            else
                draw_square(&game->screen,x * TILE_SIZE,y * TILE_SIZE,TILE_SIZE,0xc0c0c0);
            x++;
        }
        y++;
    }
}
void render_player_direction(t_game *game)
{
    int i;
    double start_x;
    double start_y;
    double end_x;
    double end_y;
    double x;
    double y;

    start_x = game->player.x * TILE_SIZE;
    start_y = game->player.y * TILE_SIZE;
    end_x   = start_x + (game->player.dir_x * 50);
    end_y   = start_y + (game->player.dir_y * 50);
    i = 0;
    while(i <= 20)
    {
        x = start_x + (end_x - start_x) * i/ 20.0;
        y = start_y + (end_y - start_y) * i / 20.0;
        put_pixel(&game->screen,(int)x,(int)y,0x00FF00);
        i++;
    }
}
void	render_player(t_game *game)
{
	int	px;
	int	py;

	px = (int)(game->player.x * TILE_SIZE);
	py = (int)(game->player.y * TILE_SIZE);
	draw_square(&game->screen, px - 4, py - 4, 8, 0xFF0000);
}