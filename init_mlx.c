#include "cub3d.h"


int close_game(t_game *game)
{
    if(game->screen.img_ptr)
        mlx_destroy_image(game->mlx,game->screen.img_ptr);
    if(game->win)
        mlx_destroy_window(game->mlx,game->win);
    if(game->mlx)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }
    exit(0);
}

int esc_close(int keycode, t_game *game)
{
    if(keycode == 65307)
        close_game(game);
    return (0);
}

void init_mlx(t_game *game)
{
    game->win_width = 1280;
    game->win_height = 720;
    game->mlx = mlx_init();
    if(!game->mlx)
        error_exit("mlx_init() failed");
    game->win = mlx_new_window(game->mlx,game->win_width,game->win_height,"Cub3D");
    if(!game->win)
    {
        error_exit("Failed MLX init");
        //close_game(game);
    }
    game->screen.img_ptr = mlx_new_image(game->mlx,game->win_width,game->win_height);
    if(!game->screen.img_ptr)
    {
        error_exit("Failed to create image");
        //close_game(game);
    }
    game->screen.addr = mlx_get_data_addr(game->screen.img_ptr,&game->screen.bpp,&game->screen.line_len,&game->screen.endian);
    if(!game->screen.addr)
    {
        error_exit("Failed to get data address");
        //close_game(game);
    }
    game->screen.width = game->win_width;
    game->screen.height = game->win_height;
}
