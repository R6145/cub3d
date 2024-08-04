#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>


#define WIN_WIDTH 800
#define WIN_HEIGHT 600

typedef struct s_data {
    void    *mlx;
    void    *win;
    int     x;
    int     y;
    float   angle;
} t_data;

typedef struct {
    int x;
    int y;
} Point;

void draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        mlx_pixel_put(mlx, win, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void rotate_point(Point *p, Point origin, float angle)
{
    float s = sin(angle);
    float c = cos(angle);

    p->x -= origin.x;
    p->y -= origin.y;

    int xnew = p->x * c - p->y * s;
    int ynew = p->x * s + p->y * c;

    p->x = xnew + origin.x;
    p->y = ynew + origin.y;
}

void fill_triangle(t_data *data, Point top, int base_width, int height, int color)
{
    Point v0 = top;
    Point v1 = { top.x - base_width / 2, top.y + height };
    Point v2 = { top.x + base_width / 2, top.y + height };

    rotate_point(&v0, top, data->angle);
    rotate_point(&v1, top, data->angle);
    rotate_point(&v2, top, data->angle);

    Point tmp;
    if (v0.y > v1.y) { tmp = v0; v0 = v1; v1 = tmp; }
    if (v0.y > v2.y) { tmp = v0; v0 = v2; v2 = tmp; }
    if (v1.y > v2.y) { tmp = v1; v1 = v2; v2 = tmp; }

    int total_height = v2.y - v0.y;
    for (int y = v0.y; y <= v2.y; y++)
    {
        int second_half = y > v1.y || v1.y == v0.y;
        int segment_height = second_half ? v2.y - v1.y : v1.y - v0.y;
        float alpha = (float)(y - v0.y) / total_height;
        float beta = (float)(y - (second_half ? v1.y : v0.y)) / segment_height;
        Point A = { v0.x + (v2.x - v0.x) * alpha, v0.y + (v2.y - v0.y) * alpha };
        Point B = second_half ? (Point){ v1.x + (v2.x - v1.x) * beta, v1.y + (v2.y - v1.y) * beta }
                              : (Point){ v0.x + (v1.x - v0.x) * beta, v0.y + (v1.y - v0.y) * beta };
        if (A.x > B.x) { tmp = A; A = B; B = tmp; }
        for (int j = A.x; j <= B.x; j++)
            mlx_pixel_put(data->mlx, data->win, j, y, color);
    }
}

int key_hook(int keycode, t_data *data)
{
    if (keycode == 65307) // Escape key
        exit(0);
    else if (keycode == 65361) // Left arrow
        data->x -= 10;
    else if (keycode == 65363) // Right arrow
        data->x += 10;
    else if (keycode == 65362) // Up arrow
        data->y -= 10;
    else if (keycode == 65364) // Down arrow
        data->y += 10;
    else if (keycode == 113) // 'q' key for rotating left
        data->angle -= 0.1;
    else if (keycode == 101) // 'e' key for rotating right
        data->angle += 0.1;

    printf("move\n");
    mlx_clear_window(data->mlx, data->win);
    Point top = { data->x, data->y };
    fill_triangle(data, top, 200, 200, 0x00FF00); // Green color
    return (0);
}

int main(void)
{
    t_data data;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Rotatable Triangle");
    data.x = WIN_WIDTH / 2;
    data.y = WIN_HEIGHT / 2;
    data.angle = 0.0;

    Point top = { data.x, data.y };
    fill_triangle(&data, top, 200, 200, 0x00FF00); // Green color

    mlx_key_hook(data.win, key_hook, &data);
    mlx_loop(data.mlx);
    return (0);
}