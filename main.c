#include "cub3d.h"



int main(int argc, char **argv)
{

    if (argc < 2)
    {
        printf("Error: missing map file argument\nUsage: %s <map_file>\n", argv[0]);
        return (1);
    }
    t_game game;
    init_game(&game);
    parse_file(&game.map,argv[1]);
    init_player(&game);
    init_mlx(&game);
    render_map(&game);
    render_player(&game);
    mlx_put_image_to_window(game.mlx,game.win,game.screen.img_ptr,0,0);
    mlx_hook(game.win,17,0,close_game,&game);
    mlx_hook(game.win,2,1L<<0,esc_close,&game);
    mlx_loop(game.mlx);
    return (0);
}