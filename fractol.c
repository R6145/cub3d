/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:39:21 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/07/22 14:05:46 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int close_window(void *param)
{
    (void)param; // Unused parameter
    exit(0);
    return (0); // To match the function signature
}

int main(void)
{
    void *mlx;
    void *window;
    void *image;
    int width;
    int height;

    // Initialize MiniLibX
    mlx = mlx_init();
    if (mlx == NULL)
    {
        fprintf(stderr, "Error: Failed to initialize MiniLibX\n");
        return EXIT_FAILURE;
    }

    // Create a new window
    window = mlx_new_window(mlx, 800, 600, "XPM Viewer");
    if (window == NULL)
    {
        fprintf(stderr, "Error: Failed to create window\n");
        return EXIT_FAILURE;
    }

    // Load the XPM image
    image = mlx_xpm_file_to_image(mlx, "Flat.xpm", &width, &height);
    if (image == NULL)
    {
        fprintf(stderr, "Error: Failed to load XPM image\n");
        return EXIT_FAILURE;
    }

    // Put the image to the window
    mlx_put_image_to_window(mlx, window, image, 0, 0);

    // Hook the destroy event to close the window properly
    mlx_hook(window, 17, 0, close_window, NULL);

    // Enter the MiniLibX event loop
    mlx_loop(mlx);

    return EXIT_SUCCESS;
}

