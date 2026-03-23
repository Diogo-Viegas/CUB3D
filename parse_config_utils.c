#include "cub3d.h"
#include "./libft/libft.h"
char	*skip_spaces(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}
int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
int starts_with(char *line, char *prefix)
{
    int i = 0;
    line = skip_spaces(line);
    while(prefix[i])
    {
        if(line[i] != prefix[i])
            return (0);
        i++;
    }
    return (1);
}
void set_texture(char **dst,char *line)
{
    char *path;
    int i;

    if(*dst != NULL)
        printf("duplicate texture\n");
    line = skip_spaces(line);
    if(*line == '\0')
        printf("missing texture path\n");
    i = 0;
    while(line[i] && line[i] != ' ' && line[i] != '\t')
        i++;
    path = ft_substr(line,0,i);
    if(!path)
        printf("Malloc Failed\n");
    line += i;
    line = skip_spaces(line);
    if(*line != '\0')
        printf("Invalid Texture format\n");
    //validar extensao .xpm
    //if(!ends_with(path, ".xpm"))
    //  printf("Texture must be .xpm\n");
    *dst = path;
}
int count_split(char **split)
{
    int i = 0;
    if(!split)
        return(0);
    while(split[i] != NULL)
        i++;
    return (i);
}
int parse_color(char *line)
{
    char **rgb;
    int r,g,b;

    line = skip_spaces(line);
    rgb = ft_split(line, ',');
    if(!rgb || count_split(rgb) != 3)
        printf("Invalid color format\n");
    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);
    
    int i = 0;
    while(rgb[i])
        free(rgb[i++]);
    free(rgb);
    if(r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        printf("Color out of range\n");
    return (r << 16 | g << 8 | b); //packs 3 8bit color values into a single 32-bit interger, standard way to represent RGB values
    //minilbx uses only one int (32 bits)

}