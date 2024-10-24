/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:46:56 by nvallin           #+#    #+#             */
/*   Updated: 2024/10/23 12:50:05 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	ft_y_ray(double direction, double *y_draw)
{
	static double	y_step = 0;

	y_step += direction;
	*y_draw += direction;
	if (direction > 0 && y_step > 8)
	{
		y_step = -8;
		return (1);
	}
	else if (direction < 0 && y_step < -8)
	{
		y_step = 8;
		return (-1);
	}
	return (0);
}

int	ft_x_ray(double direction, double *x_draw)
{
	static double	x_step = 0;

	x_step += direction;
	*x_draw += direction;
	if (direction > 0 && x_step > 8)
	{
		x_step = -8;
		return (1);
	}
	else if (direction < 0 && x_step < -8)
	{
		x_step = 8;
		return (-1);
	}
	return (0);
}

void	ft_draw_ray(t_data *data, int color)
{
	double	x;
	double	y;
	double	x_draw;
	double	y_draw;
	double	angle;
	double	dir_x;
	double	dir_y;

	angle = data->player.angle - (FOV / 2);
	while (angle < data->player.angle + (FOV / 2))
	{
		x_draw = data->player.mini_player->instances[0].x + 8;
		y_draw = data->player.mini_player->instances[0].y + 8;
		x = data->player.pos_x;
		y = data->player.pos_y;
		dir_x = cos(angle);
		dir_y = sin(angle);
		while (data->map[(int)y][(int)x] != '1')
		{
			if (((dir_x > 0 && x - data->player.pos_x < 4) || \
			(dir_x < 0 && data->player.pos_x - x < 4)) && \
			((dir_y > 0 && y - data->player.pos_y < 4) || \
			(dir_y < 0 && data->player.pos_y - y < 4)))
				mlx_put_pixel(data->img, x_draw, y_draw, color);
			y += ft_y_ray(dir_y, &y_draw);
			x += ft_x_ray(dir_x, &x_draw);
		}
		angle += 0.01;
	}
}
