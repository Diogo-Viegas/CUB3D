#include "cub3d.h"

void rotate_left(t_game *game, double angle)
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = game->player.dir_x;
    game->player.dir_x = game->player.dir_x * cos(angle) - game->player.dir_y * sin(angle);
    game->player.dir_y = old_dir_x * sin(angle) + game->player.dir_y * cos(angle);
    old_plane_x = game->player.plane_x;
    game->player.plane_x = game->player.plane_x * cos(angle) - game->player.plane_y * sin(angle);
    game->player.plane_y = old_plane_x * sin(angle) + game->player.plane_y * cos(angle);
}

void rotate_right(t_game *game, double angle)
{
    rotate_left(game,-angle);
}
void move_forward(t_game *game,double speed)
{
    double new_x;
    double new_y;

    new_x = game->player.x + game->player.dir_x * speed;
    new_y = game->player.y + game->player.dir_y * speed;

    if(game->map.grid[(int)game->player.y][(int)new_x] != '1')
        game->player.x = new_x;
    if(game->map.grid[(int)new_y][(int)game->player.x] != '1')
        game->player.y = new_y;
}
void move_backwards(t_game *game,double speed)
{
    double new_x;
    double new_y;

    new_x = game->player.x - game->player.dir_x * speed;
    new_y = game->player.y - game->player.dir_y * speed;

    if(game->map.grid[(int)game->player.y][(int)new_x] != '1')
        game->player.x = new_x;
    if(game->map.grid[(int)new_y][(int)game->player.x] != '1')
        game->player.y = new_y;
}

int key_press(int keycode, t_game *game)
{
    if(keycode == 65307) //ESC
        close_game(game);
    if(keycode == 119) //W
        move_forward(game,0.1);
    if(keycode == 115) // S
        move_backwards(game,0.1);
    if(keycode == 65361) //Right arrow
        rotate_right(game,0.1);
    if(keycode == 65363) //Left arrow
        rotate_left(game,0.1);        
    return (0);
}