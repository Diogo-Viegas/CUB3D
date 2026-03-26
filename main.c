#include "cub3d.h"

void print_map(t_map map)
{
    printf("--------------MAP--------------\n");
    printf("Height -> %d\n",map.height);
    printf("Width -> %d\n",map.width);

    int i = 0;
    while(i < map.height)
    {
        printf("%s\n",map.grid[i]);
        i++;
    }
    printf("--------------------");
}

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        printf("Expected 2 arguments");
        return (1);
    }
    t_config cfg;
    cfg.no = NULL;
    cfg.so = NULL;
    cfg.we = NULL;
    cfg.ea = NULL;
    cfg.floor = -1;
    cfg.ceiling = -1;
    t_map map;
    map.grid = NULL;
    map.height = 0;
    map.width = 0;

    char *filename = argv[1];
    char **lines;
    int i = 0;

    lines = read_file(filename);
    if (!lines)
    {
        error_exit("Failed to read file\n");
        return (1);
    }
    // while (lines[i])
    // {
    //      printf("[%d]-> %s\n", i, lines[i]);
    //      i++;
    // }
    int map_start = find_map_start(lines);       
    //printf("Map starts at line: %d\n", map_start);
    parse_config(lines,map_start,&cfg);
    printf("-----CONFIG------\n[NO] -> %s\n[SO] -> %s\n[WE] -> %s\n[EA] -> %s\n[FLOOR] -> %d\n[CEILING] -> %d\n",cfg.no,cfg.so,cfg.we,cfg.ea,cfg.floor,cfg.ceiling);
    i = 0; 
    extract_map(lines,map_start,&map);
    validate_map(&map);
    print_map(map);
    while (lines[i])
        free(lines[i++]);
    free(lines);
    return (0);
}