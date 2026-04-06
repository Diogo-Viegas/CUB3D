#include "cub3d.h"

void put_pixel(t_img *img,int x,int y,int color)
{
    char *dst;
    if(x < 0 || y < 0 || x >= img->width || y >= img->height)
        return;
    dst = img->addr + (y * img->line_len + x * (img->bpp /8));
    *(unsigned int *)dst = color;
}

void draw_square(t_img *img,int start_x,int start_y,int size,int color)
{
    int x;
    int y;

    y = 0;
    while(y < size)
    {
        x = 0;
        while(x < size)
        {
            put_pixel(img,start_x + x,start_y + y,color);
            x++;
        }
        y++;
    }
}
