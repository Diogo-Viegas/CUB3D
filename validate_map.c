#include "cub3d.h"






int validate_map(t_map *map)
{
    if(!check_chars(map))
        error_exit("Invalid characters in map");
    if(!check_player(map))
        error_exit("Invalid number of players, only one player is valid");
    if(!check_closed(map))
        error_exit("Map is not closed\n");
    return (1);
}