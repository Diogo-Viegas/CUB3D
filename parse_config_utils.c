#include "cub3d.h"
#include "./libft/libft.h"


void    error_exit(char *msg)
{
    write(2, "Error\n", 6);
    write(2, msg, ft_strlen(msg));
    write(2, "\n", 1);
    exit(1);
}
//remove spaces at the begining
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
int ends_with(char *path,char *sufix)
{
    int extension =  ft_strlen(path) - 4;
    int i = 0;
    while(path[extension] != '\0' && sufix[i] == path[extension])
    {
        extension++;
        i++;
    }
    if((int)ft_strlen(path) == extension)
        return (1);
    else
        return (0);
}
void set_texture(char **dst,char *line)
{
    char *path;
    int i;

    if(*dst != NULL)
    {
        error_exit("duplicate texture");
    }
    line = skip_spaces(line);
    if(*line == '\0')
        error_exit("Missing texture path");
    i = 0;
    while(line[i] && line[i] != ' ' && line[i] != '\t')
        i++;
    path = ft_substr(line,0,i);
    if(!path)
        printf("Malloc Failed\n");
    line += i;
    line = skip_spaces(line);
    if(*line != '\0')
        error_exit("Invalid Texture format");
    //validar extensao .xpm
    if(!ends_with(path, ".xpm"))
        error_exit("Texture must be .xpm");
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
int is_valid_number(char *s)
{
    s = skip_spaces(s);
    printf("valid s -> %s\n",s);
    if (!*s)
        return (0);
    while (*s)
    {
        if (*s < '0' || *s > '9')
            return (0);
        s++;
    }
    return (1);
}
char    *trim_spaces(char *s)
{
    char    *end;
    char    *start;

    start = s;
    while (*start == ' ' || *start == '\t')
        start++;
    if (*start == '\0')
        return (ft_strdup(""));
    end = start + ft_strlen(start) - 1;
    while (end > start && (*end == ' ' || *end == '\t'))
        end--;
    return (ft_substr(start, 0, end - start + 1));
}
static void	free_rgb(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
}

static void	trim_rgb_tokens(char **rgb)
{
	char	*trimmed;
	int		i;

	i = 0;
	while (i < 3)
	{
		trimmed = trim_spaces(rgb[i]);
		free(rgb[i]);
		rgb[i] = trimmed;
		i++;
	}
}

static void	validate_rgb(char **rgb)
{
	if (!is_valid_number(rgb[0]) ||
		!is_valid_number(rgb[1]) ||
		!is_valid_number(rgb[2]))
	{
		free_rgb(rgb);
		error_exit("Color must be a number");
	}
}

int	parse_color(char *line)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	line = skip_spaces(line);
	rgb = ft_split(line, ',');
	if (!rgb || count_split(rgb) != 3)
		error_exit("Invalid color format");
	trim_rgb_tokens(rgb);
	validate_rgb(rgb);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_rgb(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_exit("Color value out of range [0,255]");
	return (r << 16 | g << 8 | b);
}
