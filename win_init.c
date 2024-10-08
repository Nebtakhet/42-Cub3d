/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:08:12 by cesasanc          #+#    #+#             */
/*   Updated: 2024/10/08 14:15:55 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	init_color_palette(t_win *win)
{
	double	t;
	int		i;
	int		r;
	int		g;
	int		b;

	i = 1;
	win->palette[0] = 0xAA;
	while (i < ITER)
	{
		t = (double)i / (ITER / 5);
		r = (int)(win->color.r_o * (1 - t) * t * t * t * 255);
		g = (int)(win->color.g_o * (1 - t) * (1 - t) * t * t * 255);
		b = (int)(win->color.b_o * (1 - t) * (1 - t) * (1 - t) * t * 255);
		win->palette[i] = (r << 24) | (g << 16) | (b << 8) | 255;
		i++;
	}
}

void	get_layout(t_win *win)
{
	win->zoom.factor = 1.0;
	win->color.r_o = 9;
	win->color.g_o = 15;
	win->color.b_o = 8.5;
	win->renderer.frames = FRAME_WAIT;
	win->renderer.changed = true;
}

void	win_init(t_win *win)
{
	get_layout(win);
	init_color_palette(win);
	win->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!win->mlx)
		exit(EXIT_FAILURE);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	win->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	if (!win->img)
		exit(EXIT_FAILURE);
	return ;
}
