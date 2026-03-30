#include "cub3d.h"



int main(int argc, char **argv)
{

    if (argc < 2)
    {
        printf("Expected 2 arguments");
        return (1);
    }
    t_game game;
    init_game(&game);
    parse_file(&game.map,argv[1]);
    return (0);
}