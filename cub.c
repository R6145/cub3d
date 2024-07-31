/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:39:21 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/07/31 16:08:04 by fmaqdasi         ###   ########.fr       */
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

void	map_save(char **map, char *path)
{
	int		i;
	char	temp;
	int		fd;

	i = 0;
	map = malloc(10000);
	fd = open(path);
	map[0] = get_next_line(fd);
	while (map[i] != NULL)
		map[i++] = get_next_line(fd);
}

int	main(void)
{
	t_mlx	mlx;
	char	**map;
	int		rows;
	int		cols;

	// map[] = {"1111111111111111111111111", "1000000000110000000000001",
	// 	"1011000001110000000000001", "1001000000000000000000001",
	// 	"111111111011000001110000000000001",
	// 	"100000000011000001110111111111111", "11110111111111011100000010001",
	// 	"11110111111111011101010010001", "11000000110101011100000010001",
	// 	"10000000000000001100000010001", "10000000000000001101010010001",
	// 	"11000001110101011111011110N0111", "11110111 1110101 101111010001",
	// 	"11111111 1111111 111111111111"};
	map_save(map, map.txt);
	rows = sizeof(map) / sizeof(map[0]);
	cols = ft_strlen(map[0]);
	int i, j;
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "Map Display");
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (map[i][j] == '1')
				draw_tile(mlx.mlx_ptr, mlx.win_ptr, j, i, 0xFFFFFF);
			// White color for walls
			else if (map[i][j] == '0')
				draw_tile(mlx.mlx_ptr, mlx.win_ptr, j, i, 0x000000);
			// Black color for empty space
			else if (map[i][j] == 'N')
				draw_tile(mlx.mlx_ptr, mlx.win_ptr, j, i, 0xFF0000);
			// Red color for a special item
			else if (map[i][j] == ' ')
				draw_tile(mlx.mlx_ptr, mlx.win_ptr, j, i, 0x0000FF);
			// Blue color for open space
		}
	}
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
