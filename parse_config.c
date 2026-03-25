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
void parse_texture_line(char *line,t_config *cfg)
{
    line = skip_spaces(line);
    if(starts_with(line,"NO "))
        set_texture(&cfg->no,line + 2);
    else if (starts_with(line,"SO "))
        set_texture(&cfg->so,line + 2);
    else if(starts_with(line,"WE "))
        set_texture(&cfg->we,line + 2);
    else if(starts_with(line,"EA "))
        set_texture(&cfg->ea,line + 2);
    else
        error_exit("Invalid texture identifier");
}

void parse_color_line(char *line,t_config *cfg)
{   

    line = skip_spaces(line);
    if(starts_with(line,"F "))
    {
        if(cfg->floor != -1)
            error_exit("Duplicate floor color");
         cfg->floor = parse_color(line + 2);
    }       
    else if(starts_with(line, "C "))
    {
        if(cfg->ceiling != -1)
            error_exit("Duplicate ceiling color");
        cfg->ceiling = parse_color(line + 2);
    }
        
}
void validate_config(t_config *cfg)
{
    if(!cfg->no || !cfg->so || !cfg->we || !cfg->ea)
        error_exit("Missing Textures");
    if(cfg->ceiling == -1 || cfg->floor == -1)
        error_exit("Missing Color");
}
void parse_config(char **lines, int map_start,t_config *cfg)
{
    int i = 0;
    while(i < map_start)
    {
        if(is_empty_line(lines[i]))
            ;
        else if(is_texture_line(lines[i]))
            parse_texture_line(lines[i],cfg);
        else if(is_color_line(lines[i]))
            parse_color_line(lines[i],cfg);
        else
            error_exit("Invalid config line");
        i++;
    }
   validate_config(cfg);
}
