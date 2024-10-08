/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:08:12 by cesasanc          #+#    #+#             */
/*   Updated: 2024/10/08 14:56:25 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	init_color_palette(t_data *data)
{
	double	t;
	int		i;
	int		r;
	int		g;
	int		b;

	i = 1;
	data->palette[0] = 0xAA;
	while (i < ITER)
	{
		t = (double)i / (ITER / 5);
		r = (int)(data->color.r_o * (1 - t) * t * t * t * 255);
		g = (int)(data->color.g_o * (1 - t) * (1 - t) * t * t * 255);
		b = (int)(data->color.b_o * (1 - t) * (1 - t) * (1 - t) * t * 255);
		data->palette[i] = (r << 24) | (g << 16) | (b << 8) | 255;
		i++;
	}
}

void	get_layout(t_data *data)
{
	data->zoom.factor = 1.0;
	data->color.r_o = 9;
	data->color.g_o = 15;
	data->color.b_o = 8.5;
	data->renderer.frames = FRAME_WAIT;
	data->renderer.changed = true;
}

void	win_init(t_data *data)
{
	get_layout(data);
	init_color_palette(data);
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!data->mlx)
		exit(EXIT_FAILURE);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
		exit(EXIT_FAILURE);
	return ;
}
