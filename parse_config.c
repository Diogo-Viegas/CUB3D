#include "cub3d.h"
#include "./libft/libft.h"

int is_color_line(char *line)
{
    return (starts_with(line,"F ") || starts_with(line,"C "));
}

int is_texture_line(char *line)
{
    return(starts_with(line,"NO ") || 
            starts_with(line,"SO ") || 
            starts_with(line,"WE ") || 
            starts_with(line,"EA ")
        );
}
void parse_texture_line(char *line,t_map *map)
{
    line = skip_spaces(line);
    if(starts_with(line,"NO "))
        set_texture(&map->no,line + 2);
    else if (starts_with(line,"SO "))
        set_texture(&map->so,line + 2);
    else if(starts_with(line,"WE "))
        set_texture(&map->we,line + 2);
    else if(starts_with(line,"EA "))
        set_texture(&map->ea,line + 2);
    else
        error_exit("Invalid texture identifier");
}

void parse_color_line(char *line,t_map *map)
{   

    line = skip_spaces(line);
    if(starts_with(line,"F "))
    {
        if(map->floor != -1)
            error_exit("Duplicate floor color");
         map->floor = parse_color(line + 2);
    }       
    else if(starts_with(line, "C "))
    {
        if(map->ceiling != -1)
            error_exit("Duplicate ceiling color");
        map->ceiling = parse_color(line + 2);
    }
        
}
void validate_config(t_map *map)
{
    if(!map->no || !map->so || !map->we || !map->ea)
        error_exit("Missing Textures");
    if(map->ceiling == -1 || map->floor == -1)
        error_exit("Missing Color");
}
void parse_config(char **lines, int map_start,t_map *map)
{
    int i = 0;
    while(i < map_start)
    {
        if(is_empty_line(lines[i]))
            ;
        else if(is_texture_line(lines[i]))
            parse_texture_line(lines[i],map);
        else if(is_color_line(lines[i]))
            parse_color_line(lines[i],map);
        else
            error_exit("Invalid config line");
        i++;
    }
   validate_config(map);
}
