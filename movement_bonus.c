/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
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

void	ft_move_player_y(t_data *data, double direction)
{
	static double	pixels = 0;

	if ((direction < 0 && !ft_is_player_near_wall(data, 'y', -1)) \
		&& !ft_is_near_door(data, 'y', -1))
	{
		data->player.pos_y += direction / 20.0;
		pixels += direction / 1.25;
		if (pixels <= -1)
		{
			ft_move_minimap_y(data, direction);
			pixels += 1;
		}
	}
	else if (direction > 0 && !ft_is_player_near_wall(data, 'y', 1) \
			&& !ft_is_near_door(data, 'y', 1))
	{
		data->player.pos_y += direction / 20.0;
		pixels += direction / 1.25;
		if (pixels >= 1)
		{
			ft_move_minimap_y(data, direction);
			pixels -= 1;
		}		
	}		
}

void	ft_move_player_x(t_data *data, double direction)
{
	static double	pixels = 0;

	if (direction < 0 && !ft_is_player_near_wall(data, 'x', -1) && \
		!ft_is_near_door(data, 'x', -1))
	{
		data->player.pos_x += direction / 20.0;
		pixels += direction / 1.25;
		if (pixels <= -1)
		{
			ft_move_minimap_x(data, direction);
			pixels += 1;
		}
	}
	else if (direction > 0 && !ft_is_player_near_wall(data, 'x', 1) \
			&& !ft_is_near_door(data, 'x', 1))
	{
		data->player.pos_x += direction / 20.0;
		pixels += direction / 1.25;
		if (pixels >= 1)
		{
			ft_move_minimap_x(data, direction);
			pixels -= 1;
		}	
	}
}

void	ft_move_player(t_data *data, double dir_y, double dir_x)
{
	ft_move_player_y(data, dir_y);
	ft_move_player_x(data, dir_x);
	data->player.moved = true;
	data->renderer.changed = true;
}
