/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 14:47:26 by fmaqdasi          #+#    #+#             */
/*   Updated: 2024/07/31 16:05:14 by fmaqdasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 800
# define HEIGHT 800
# define TILE_SIZE 20
# define BUFFER_SIZE 0

// typedef struct s_movement
// {
// 	double		scale;
// 	double		offset_x;
// 	double		offset_y;
// 	double		offset_fix;
// 	double		zoom;
// 	int			iterations;
// 	int			color_scheme[3];
// 	double		cr;
// 	double		ci;
// 	int			fractol_choice;
// }				t_movemet;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	// t_movemet	move;
}			t_mlx;

char		*get_next_line(int fd);

#endif