/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:39:21 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/08/04 17:44:40 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// int close_window(void *param)
// {
//     (void)param; // Unused parameter
//     exit(0);
//     return (0); // To match the function signature
// }

// int main(void)
// {
//     void *mlx;
//     void *window;
//     void *image;
//     int width;
//     int height;

//     // Initialize MiniLibX
//     mlx = mlx_init();
//     if (mlx == NULL)
//     {
//         fprintf(stderr, "Error: Failed to initialize MiniLibX\n");
//         return (EXIT_FAILURE);
//     }

//     // Create a new window
//     window = mlx_new_window(mlx, 800, 600, "XPM Viewer");
//     if (window == NULL)
//     {
//         fprintf(stderr, "Error: Failed to create window\n");
//         return (EXIT_FAILURE);
//     }

//     // Load the XPM image
//     image = mlx_xpm_file_to_image(mlx, "Flat.xpm", &width, &height);
//     if (image == NULL)
//     {
//         fprintf(stderr, "Error: Failed to load XPM image\n");
//         return (EXIT_FAILURE);
//     }

//     // Put the image to the window
//     mlx_put_image_to_window(mlx, window, image, 0, 0);

//     // Hook the destroy event to close the window properly
//     mlx_hook(window, 17, 0, close_window, NULL);

//     // Enter the MiniLibX event loop
//     mlx_loop(mlx);

//     return (EXIT_SUCCESS);
// }

// typedef struct s_vars {
//     void    *mlx;
//     void    *win;
// }   t_vars;

void	draw_tile(void *mlx, void *win, int x, int y, int color)
{
	int i, j;
	for (i = 0; i < TILE_SIZE; i++)
	{
		for (j = 0; j < TILE_SIZE; j++)
		{
			mlx_pixel_put(mlx, win, x * TILE_SIZE + i, y * TILE_SIZE + j,
				color);
		}
	}
}

char	**map_save(char **map, char *path)
{
	int		i;
	char	temp;
	int		fd;

	i = 1;
	map = malloc(10000);
	fd = open(path, O_RDONLY);
	map[0] = get_next_line(fd);
	while (map[i] != NULL)
		map[i++] = get_next_line(fd);
	map[i] = NULL;
	i = 0;
	printf("%s\n", map[0]);
	while (map[i] != NULL)
		printf("%s\n", map[i++]);
	close(fd);
	return (map);
}

void	draw_player(void *mlx, void *win, int x, int y, int color)
{
	int	i;

	for (i = 0; i < TILE_SIZE; i++)
	{
		mlx_pixel_put(mlx, win, x * TILE_SIZE + i, y * TILE_SIZE, color);
		mlx_pixel_put(mlx, win, x * TILE_SIZE + TILE_SIZE / 2, y * TILE_SIZE
			- i, color);
		mlx_pixel_put(mlx, win, x * TILE_SIZE + TILE_SIZE - i, y * TILE_SIZE,
			color);
	}
}

int	key_press(int keycode, t_mlx *mlx)
{
	if (keycode == 65307) // Escape key
		exit(0);
	if (keycode == 65361) // Left arrow key
		mlx->player_x--;
	if (keycode == 65362) // Up arrow key
		mlx->player_y--;
	if (keycode == 65363) // Right arrow key
		mlx->player_x++;
	if (keycode == 65364) // Down arrow key
		mlx->player_y++;
	render_next_frame(&mlx);
	return (0);
}

// int	main(void)
// {
// 	t_mlx	mlx;
// 	char	**map;
// 	int		rows;
// 	int		cols;

// 	map = map_save(map, "map.txt");
// 	rows = 33;
// 	cols = 14;
// 	int i, j;
// 	mlx.mlx_ptr = mlx_init();
// 	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "Map Display");
// 	i = 0;
// 	while (map[i] != NULL)
// 	{
// 		j = 0;
// 		while (map[i][j] != '\0')
// 		{
// 			if (map[i][j] == '1')
// 				draw_tile(mlx.mlx_ptr, mlx.win_ptr, j, i, 0xFFFFFF);
// 			// White color for walls
// 			else if (map[i][j] == '0')
// 				draw_tile(mlx.mlx_ptr, mlx.win_ptr, j, i, 0x000000);
// 			// Black color for empty space
// 			else if (map[i][j] == 'N')
// 				draw_tile(mlx.mlx_ptr, mlx.win_ptr, j, i, 0xFF0000);
// 			// Red color for a special item
// 			else if (map[i][j] == ' ')
// 				draw_tile(mlx.mlx_ptr, mlx.win_ptr, j, i, 0x0000FF);
// 			// Blue color for open space
// 			j++;
// 		}
// 		i++;
// 	}
// 	mlx_loop(mlx.mlx_ptr);
// 	return (0);
// }

int	render_next_frame(t_mlx *mlx)
{
	char	**map;
	int i, j;
	// Clear the window
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	// Redraw the map
	map = map_save(map, "map.txt");
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '1')
				draw_tile(mlx->mlx_ptr, mlx->win_ptr, j, i, 0xFFFFFF);
			else if (map[i][j] == '0')
				draw_tile(mlx->mlx_ptr, mlx->win_ptr, j, i, 0x000000);
			else if (map[i][j] == 'N')
				draw_tile(mlx->mlx_ptr, mlx->win_ptr, j, i, 0xFF0000);
			else if (map[i][j] == ' ')
				draw_tile(mlx->mlx_ptr, mlx->win_ptr, j, i, 0x0000FF);
			j++;
		}
		i++;
	}
	draw_player(mlx->mlx_ptr, mlx->win_ptr, mlx->player_x, mlx->player_y,
		0x00FF00);
	return (0);
}

int	main(void)
{
	t_mlx mlx;

	mlx.player_x = 1;
	mlx.player_y = 1;
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "Map Display");
	render_next_frame(&mlx);

	mlx_key_hook(mlx.win_ptr, key_press, &mlx);
	// mlx_loop_hook(mlx.mlx_ptr, render_next_frame, &mlx);
	mlx_loop(mlx.mlx_ptr);

	return (0);
}