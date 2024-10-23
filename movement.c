/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:54:53 by nvallin           #+#    #+#             */
/*   Updated: 2024/10/23 12:51:05 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	ft_rotate_player(t_data *data, char direction)
{
	if (direction == 'l')
	{
		data->player.angle -= PI / 90;
		if (data->player.angle < 0)
			data->player.angle += 2 * PI;
		data->player.dir_x = cos(data->player.angle);
		data->player.dir_y = sin(data->player.angle);
		data->player.plane_x = -sin(data->player.angle) * 0.66;
		data->player.plane_y = cos(data->player.angle) * 0.66;
	}
	if (direction == 'r')
	{
		data->player.angle += PI / 90;
		if (data->player.angle > 2 * PI)
			data->player.angle -= 2 * PI;
		data->player.dir_x = cos(data->player.angle);
		data->player.dir_y = sin(data->player.angle);
		data->player.plane_x = -sin(data->player.angle) * 0.66;
		data->player.plane_y = cos(data->player.angle) * 0.66;
	}
	data->player.moved = true;
}

int	ft_is_player_near_wall(t_data *data, char axis, int direction)
{
	double	y;
	double	x;

	y = data->player.pos_y;
	x = data->player.pos_x;
	if (axis == 'y')
	{
		if (direction > 0 && data->map[(int)(y + 0.375)][(int)x] == '1')
			return (1);
		if (direction < 0 && data->map[(int)(y - 0.375)][(int)x] == '1')
			return (1);
	}
	if (axis == 'x')
	{
		if (direction > 0 && data->map[(int)y][(int)(x + 0.375)] == '1')
			return (1);
		if (direction < 0 && data->map[(int)y][(int)(x - 0.375)] == '1')
			return (1);
	}
	return (0);
}

void	ft_move_player_up(t_data *data, double direction)
{
	static double	y_moved = 0;
	static double	pixels = 0;

	if (!ft_is_player_near_wall(data, 'y', -1))
	{
		pixels += direction;
		if (pixels <= -1)
		{
			data->player.mini_player->instances[0].y--;
			data->player.pos_y -= 0.0625;
			y_moved += 0.0625;
			pixels += 1;
			if (y_moved >= 0.5)
			{
				data->player_pos[0] -= 1;
				y_moved -= 1;
			}
		}
	}
}

void	ft_move_player_down(t_data *data, double direction)
{
	static double	y_moved = 0;
	static double	pixels = 0;

	if (!ft_is_player_near_wall(data, 'y', 1))
	{
		pixels += direction;
		if (pixels >= 1)
		{
			data->player.mini_player->instances[0].y++;
			data->player.pos_y += 0.0625;
			y_moved += 0.0625;
			pixels -= 1;
			if (y_moved >= 0.5)
			{
				data->player_pos[0] += 1;
				y_moved -= 1;
			}
		}
	}
}

void	ft_move_player_left(t_data *data, double direction)
{
	static double	x_moved = 0;
	static double	pixels = 0;

	if (!ft_is_player_near_wall(data, 'x', -1))
	{
		pixels += direction;
		if (pixels <= -1)
		{
			data->player.mini_player->instances[0].x--;
			data->player.pos_x -= 0.0625;
			x_moved += 0.0625;
			pixels += 1;
			if (x_moved >= 0.5)
			{
				data->player_pos[1] -= 1;
				x_moved -= 1;
			}
		}
	}
}

void	ft_move_player_right(t_data *data, double direction)
{
	static double	x_moved = 0;
	static double	pixels = 0;

	if (!ft_is_player_near_wall(data, 'x', 1))
	{
		pixels += direction;
		if (pixels >= 1)
		{
			data->player.mini_player->instances[0].x++;
			data->player.pos_x += 0.0625;
			x_moved += 0.0625;
			pixels -= 1;
			if (x_moved >= 0.5)
			{
				data->player_pos[1] += 1;
				x_moved -= 1;
			}
		}
	}
}

void	ft_move_player(t_data *data, double dir_y, double dir_x)
{
	if (dir_y < 0)
		ft_move_player_up(data, dir_y);
	else if (dir_y > 0)
		ft_move_player_down(data, dir_y);
	if (dir_x < 0)
		ft_move_player_left(data, dir_x);
	else if (dir_x > 0)
		ft_move_player_right(data, dir_x);
	data->player.moved = true;
	data->renderer.changed = true;
}
