/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:21:25 by cesasanc          #+#    #+#             */
/*   Updated: 2024/10/08 12:20:57 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <math.h>
#include <stdlib.h>
# include <string.h>
# include "MLX42/include/MLX42/MLX42.h"

# define HEIGHT 800
# define WIDTH 800
# define ITER 69
# define FRAME_WAIT 5

typedef struct s_cords
{
	double	min;
	double	max;
}				t_cords;

typedef struct s_complex
{
	double	r;
	double	i;
}				t_complex;

typedef struct s_renderer
{
	int		frames;
	bool	changed;
}				t_renderer;

typedef struct s_color
{
	double		r_o;
	double		g_o;
	double		b_o;
}				t_color;

typedef struct s_zoom
{
	double	x;
	double	y;
	double	factor;
	double	level;
}				t_zoom;

typedef struct s_mouse
{
	int32_t	x;
	int32_t	y;
}				t_mouse;

typedef struct s_win
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	u_int32_t	iter;
	t_cords		x;
	t_cords		y;
	t_complex	complex;
	u_int32_t	palette[ITER];
	t_color		color;
	t_renderer	renderer;
	t_zoom		zoom;
	t_mouse		mouse;
}				t_win;

#endif