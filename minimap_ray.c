/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:46:56 by nvallin           #+#    #+#             */
/*   Updated: 2024/10/21 09:51:27 by cesasanc         ###   ########.fr       */
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

static void draw_fov(t_data *data)
{
	double	x;
	double	y;
	double	angle;
	double	dir_x;
	double	dir_y;

	angle = data->player.angle - (FOV / 2);
	while (angle < data->player.angle + (FOV / 2))
	{
		x = data->player.mini_player->instances[0].x + 8;
		y = data->player.mini_player->instances[0].y + 8;
		dir_x = cos(angle);
		dir_y = sin(angle);
		while (data->map[(int)y / 16][(int)x / 16] != '1')
		{
			mlx_put_pixel(data->img, (int)x, (int)y, data->palette[12]);
			y += dir_y * 0.1;
			x += dir_x * 0.1;
		}
		angle += 0.01;
	}
}

void	ft_draw_ray(t_data *data, int color)
{
	int x;
	int	y;
	double	x_draw;
	double	y_draw;

	x_draw = data->player.mini_player->instances[0].x + 8;
	y_draw = data->player.mini_player->instances[0].y + 8;
	x = data->player_pos[1];
	y = data->player_pos[0];
	while (data->map[y][x] != '1')
	{
		mlx_put_pixel(data->img, x_draw, y_draw, color);
		y += ft_y_ray(data->player.dir_y, &y_draw);
		x += ft_x_ray(data->player.dir_x, &x_draw);
	}
	draw_fov(data);
}
