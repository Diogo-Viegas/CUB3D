#include "cub3d.h"
#include "./libft/libft.h"

int is_config_line(char *line)
{
    line = skip_spaces(line);
    return(starts_with(line, "NO ") ||
            starts_with(line,"SO ") ||
            starts_with(line,"WE ") ||
            starts_with(line,"EA ") ||
            starts_with(line,"F ")  ||
            starts_with(line,"C "));
}
int find_map_start(char **lines)
{
    int i = 0;
    while (lines[i])
        i++;
    // percorre de baixo para cima
    i--;
    while (i >= 0 && is_empty_line(lines[i]))
        i--;
    // agora lines[i] é a última linha do mapa
    // sobe até encontrar a primeira linha de mapa
    while (i >= 0 && !is_config_line(lines[i]) && !is_empty_line(lines[i]))
        i--;
    return (i + 1);
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
        error_exit("Failed to open file at count liness");
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
        error_exit("File must have .cub extension");
    count = count_lines(file);
    if(count == 0)
        error_exit("File is empty");
    fd = open(file,O_RDONLY);
    if(fd < 0)
        error_exit("Failed to open file at read file");
    lines = malloc(sizeof(char *) * (count + 1));
    if(!lines)
        error_exit("Malloc failed");
    while((line = get_next_line(fd)))
    {
        trim_newline(line);
        lines[i++] = line;
    }
    lines[i] = NULL;
    close(fd);
    return(lines);
}


