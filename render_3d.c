#include "cub3d.h"


void draw_vertical_line(t_game *game, int x, int drawStart, int drawEnd, int color)
{
    int y;
    
    y = 0;
    while(y < drawStart)
    {
        put_pixel(&game->screen,x,y,game->map.ceiling);
        y++;
    }
    while(y <= drawEnd)
    {
        put_pixel(&game->screen,x,y,color);
        y++;
    }
    while(y < game->win_height)
    {
        put_pixel(&game->screen,x,y,game->map.floor);
        y++;
    }
}

void calc_wall_height(t_game *game,t_ray *ray)
{
    
    ray->lineHeight = (int)(game->win_height / ray->perpWallDist);
    printf("Ray->lineHeight : %d\n",ray->lineHeight);
    ray->drawStart = -ray->lineHeight / 2 + game->win_height / 2;
    ray->drawEnd = ray->lineHeight / 2 + game->win_height / 2;
    if(ray->drawStart < 0)
        ray->drawStart = 0;
    if(ray->drawEnd >= game->win_height)
        ray->drawEnd = game->win_height -1;

}