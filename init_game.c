#include "cub3d.h"
void print_map(t_map *map)
{
    printf("--------------MAP--------------\n");
    printf("Height -> %d\n",map->height);
    printf("Width -> %d\n",map->width);

    int i = 0;
    while(i < map->height)
    {
        printf("%s\n",map->grid[i]);
        i++;
    }
    printf("----------------------------------------\n");
}
void init_game(t_game *game)
{
    ft_memset(game,0,sizeof(t_game));
    game->map.ceiling = -1;
    game->map.floor = -1;
}

void parse_file(t_map *map,char *filename)
{
    char **lines;
    lines = read_file(filename);
    if(!lines)
        error_exit("Failed to read file\n");
    int map_start = find_map_start(lines);
    parse_config(lines,map_start,map);
    printf("-----CONFIG------\n[NO] -> %s\n[SO] -> %s\n"
        "[WE] -> %s\n[EA] -> %s\n[FLOOR] -> %d\n[CEILING] -> %d\n"
        ,map->no,map->so,map->we,map->ea,map->floor,map->ceiling);
    extract_map(lines,map_start,map);
    free_array(lines);
    validate_map(map);
    print_map(map);

}
void set_player_dir(t_player *player,char dir)
{
    if(dir == 'N')
    {
        player->dir_x = 0;
        player->dir_y = -1;
    }
    else if(dir == 'S')
    {
        player->dir_x = 0;
        player->dir_y = 1;
    }
    else if(dir == 'W')
    {
        player->dir_x = -1;
        player->dir_y = 0;
    }
    else if(dir == 'E')
    {
        player->dir_x = 1;
        player->dir_y = 0;

    }
}
void set_player_fov(t_player *player,char dir)
{
    if(dir == 'N')
    {
        player->plane_x = 0.66;
        player->plane_y = 0;
    }
    else if(dir == 'S')
    {
        player->plane_x = -0.66;
        player->plane_y = 0;
    }
    else if(dir == 'W')
    {
        player->plane_x = 0;
        player->plane_y = -0.66;
    }
    else if(dir == 'E')
    {
        player->plane_x = 0;
        player->plane_y = 0.66;
    }
}
void init_player(t_game *game)
{
    int y;
    int x;
    char dir;
    
    dir = find_player(&game->map,&x,&y);
    game->player.x = x + 0.5;
    game->player.y = y + 0.5 ;
    set_player_dir(&game->player,dir);
    game->map.grid[y][x] = '0';
    set_player_fov(&game->player,dir);
    printf("[Player] -> [%0.2f] [%0.2f]\n",game->player.y,game->player.x);
    printf("[Player Dir x] -> %f\n",game->player.dir_x);
    printf("[Player Dir y] -> %f\n",game->player.dir_y);
    printf("[Player Fov x] -> %f\n",game->player.plane_x);
    printf("[Player Fov y] -> %f\n",game->player.plane_y);
}
