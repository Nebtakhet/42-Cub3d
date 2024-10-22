/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:54:53 by nvallin           #+#    #+#             */
/*   Updated: 2024/10/22 12:56:24 by cesasanc         ###   ########.fr       */
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
	}
	if (direction == 'r')
	{
		data->player.angle += PI / 90;
		if (data->player.angle > 2 * PI)
			data->player.angle -= 2 * PI;
		data->player.dir_x = cos(data->player.angle);
		data->player.dir_y = sin(data->player.angle);
	}
	data->player.moved = true;
}

int	ft_is_player_near_wall(t_data *data, char axis, int direction)
{
	int	y;
	int	x;

	y = data->player_pos[0];
	x = data->player_pos[1];
	if (axis == 'y')
	{
		if (direction > 0 && data->map[y + 1][x] == '1')
			return (1);
		if (direction < 0 && data->map[y - 1][x] == '1')
			return (1);
	}
	if (axis == 'x')
	{
		if (direction > 0 && data->map[y][x + 1] == '1')
			return (1);
		if (direction < 0 && data->map[y][x - 1] == '1')
			return (1);		
	}
	return (0);
}

void	ft_move_player_up(t_data *data, double direction)
{
	static int		y_moved = 0;
	static double	pixels = 0;

	if (!ft_is_player_near_wall(data, 'y', -1) || \
		(ft_is_player_near_wall(data, 'y', -1) && y_moved > -5))
	{
		pixels += direction;
		if (pixels <= -1)
		{
			data->player.mini_player->instances[0].y--;
			data->player.pos_y--;
			pixels += 1;
			if (--y_moved < -8)
			{
				data->player_pos[0] -= 1;
				y_moved += 16;
			}
		}
	}
}

void	ft_move_player_down(t_data *data, double direction)
{
	static int		y_moved = 0;
	static double	pixels = 0;

	if (!ft_is_player_near_wall(data, 'y', 1) || \
		(ft_is_player_near_wall(data, 'y', 1) && y_moved < 5))
	{
		pixels += direction;
		if (pixels >= 1)
		{
			data->player.mini_player->instances[0].y++;
			data->player.pos_y++;
			pixels -= 1;
			if (++y_moved > 8)
			{
				data->player_pos[0] += 1;
				y_moved -= 16;
			}
		}
	}
}

void	ft_move_player_left(t_data *data, double direction)
{
	static int		x_moved = 0;
	static double	pixels = 0;

	if (!ft_is_player_near_wall(data, 'x', -1) || \
		(ft_is_player_near_wall(data, 'x', -1) && x_moved > -5))
	{
		pixels += direction;
		if (pixels <= -1)
		{
			data->player.mini_player->instances[0].x--;
			data->player.pos_x--;
			pixels += 1;
			if (--x_moved < -8)
			{
				data->player_pos[1] -= 1;
				x_moved += 16;
			}
		}
	}
}

void	ft_move_player_right(t_data *data, double direction)
{
	static int		x_moved = 0;
	static double	pixels = 0;

	if (!ft_is_player_near_wall(data, 'x', 1) || \
		(ft_is_player_near_wall(data, 'x', 1) && x_moved < 5))
	{
		pixels += direction;
		if (pixels >= 1)
		{
			data->player.mini_player->instances[0].x++;
			data->player.pos_x++;
			pixels -= 1;
			if (++x_moved > 8)
			{
				data->player_pos[1] += 1;
				x_moved -= 16;
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
