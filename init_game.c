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
    printf("--------------------");
}
void init_game(t_game *game)
{
    ft_memset(game,0,sizeof(t_game));
    game->win_width = 1280;
    game->win_height = 720;
    game->map.ceiling = -1;
    game->map.floor = -1;
}

void parse_file(t_map *map,char *filename)
{
    char **lines;
    int i = 0;
    lines = read_file(filename);
    if(!lines)
        error_exit("Failed to read file\n");
    int map_start = find_map_start(lines);
    parse_config(lines,map_start,map);
    printf("-----CONFIG------\n[NO] -> %s\n[SO] -> %s\n"
        "[WE] -> %s\n[EA] -> %s\n[FLOOR] -> %d\n[CEILING] -> %d\n"
        ,map->no,map->so,map->we,map->ea,map->floor,map->ceiling);
    i = 0;
    extract_map(lines,map_start,map);
    validate_map(map);
    print_map(map);
    while (lines[i])
        free(lines[i++]);
    free(lines);
}
