#ifndef CUB32_H
# define CUB32_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

typedef struct s_config
{
    char *no;
    char *so;
    char *we;
    char *ea;
    int floor; //default -1;
    int ceiling; //default -1;
}t_config;

//parse_config.c
int is_color_line(char *line);
int is_texture_line(char *line);
void parse_texture_line(char *line,t_config *cfg);
void parse_color_line(char *line,t_config *cfg);
void validate_config(t_config *cfg);
void parse_config(char **lines, int map_start,t_config *cfg);

//parse_config_utils.c
char	*skip_spaces(char *line);
int	is_empty_line(char *line);
int starts_with(char *line, char *prefix);
void set_texture(char **dst,char *line);
int count_split(char **split);
int parse_color(char *line);

#endif