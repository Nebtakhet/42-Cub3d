/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:46:56 by nvallin           #+#    #+#             */
/*   Updated: 2024/10/22 12:54:05 by cesasanc         ###   ########.fr       */
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
	int 	x;
	int		y;
	double	x_draw;
	double	y_draw;

	x_draw = data->player.mini_player->instances[0].x + 8;
	y_draw = data->player.mini_player->instances[0].y + 8;
	x = (int)x_draw;
	y = (int)y_draw;
	while (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT && data->map[y][x] != '1')
	{
		printf("Drawing at (%d, %d)\n", x, y);
        mlx_put_pixel(data->img, x_draw, y_draw, color);
        x_draw += data->ray.ray_dir_x * 0.1;
        y_draw += data->ray.ray_dir_y * 0.1;
        x = (int)x_draw;
		y = (int)y_draw;
	}

}
