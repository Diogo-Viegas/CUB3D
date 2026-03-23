#include "cub3d.h"
#include "./libft/libft.h"

int is_map_line(char *line)
{
    int i = 0;
    int has_map_char = 0;
    while (line[i])
    {
        if(line[i] != ' ' && line[i] != '1' && 
            line[i] != '0' && line[i] != 'N' && 
            line[i] != 'S' && line[i] != 'W' && line[i] != 'E')
            return (0);
        if(line[i] != ' ')
            has_map_char = 1;
        i++;
    }
    return (has_map_char);
}
int find_map_start(char **lines)
{
    int i = 0;
    while (lines[i])
    {
        if (is_map_line(lines[i]))
            return (i);
        i++;
    }
    return (-1);
}

void trim_newline(char *line)
{
    int len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
}

int count_lines(char *file)
{
    int fd;
    int count = 0;
    char *line;

    fd = open(file,O_RDONLY);
    if(fd < 0)
        printf("Failed to open file at count liness\n");
    while((line = get_next_line(fd)))
    {
        count++;
        free(line);
    }
    close(fd);
    return (count);
}
int is_cub(char *file)
{
    return(ft_strnstr(file, ".cub", ft_strlen(file)) != NULL);
}
char **read_file(char *file)
{
    int fd;
    int i = 0;
    int count;
    char **lines;
    char *line;
    if(!is_cub(file))
    {
        printf("File must have .cub extension\n");
        exit(1);
    }
    count = count_lines(file);
    if(count == 0)
    {
        printf("File is empty\n");
        exit(1);
    }
    fd = open(file,O_RDONLY);
    if(fd < 0)
        printf("Failed to open file at read file\n");
    lines = malloc(sizeof(char *) * (count + 1));
    if(!lines)
        printf("Malloc failed\n");
    while((line = get_next_line(fd)))
    {
        trim_newline(line);
        lines[i++] = line;
    }
    lines[i] = NULL;
    close(fd);
    return(lines);
}
int main(int argc, char **argv)
{

    if (argc < 2)
    {
        perror("Expected 2 arguments");
        return (1);
    }
    t_config cfg;
    cfg.floor = -1;
    cfg.ceiling = -1;
    char *filename = argv[1];
    char **lines;
    int i = 0;

    lines = read_file(filename);
    if (!lines)
    {
        perror("Failed to read file\n");
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
    printf("-----CONFIG------\n[NO] -> %s\n[SO] -> %s\n[WE] -> %s\n[EA] -> %s\n [FLOOR] -> %d\n[CEILING] -> %d\n",cfg.no,cfg.so,cfg.we,cfg.ea,cfg.floor,cfg.ceiling);
    i = 0; 
    while (lines[i])
        free(lines[i++]);
    free(lines);
    return (0);
}