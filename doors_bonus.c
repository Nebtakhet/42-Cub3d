/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:14:56 by cesasanc          #+#    #+#             */
/*   Updated: 2024/11/05 11:53:27 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	ft_get_door_texture(t_data *data)
{
	data->door_texture = mlx_load_png("textures/eagle.png");
	if (!data->door_texture)
	{
		write(2, "Error\ninvalid door texture\n", 27);
		return (1);
	}
	return (0);
}

int	ft_is_near_door(t_data *data, char axis, int direction)
{
	double	y;
	double	x;

	y = data->player.pos_y;
	x = data->player.pos_x;
	if (axis == 'y')
	{
		if ((direction > 0 && data->map[(int)(y + 0.5)][(int)x] == 'D')
			|| (direction < 0 && data->map[(int)(y - 0.5)][(int)x] == 'D'))
			return (1);
		if ((direction > 0 && data->map[(int)(y + 0.5)][(int)x] == 'd')
			|| (direction < 0 && data->map[(int)(y - 0.5)][(int)x] == 'd'))
			return (2);
	}
	if (axis == 'x')
	{
		if ((direction > 0 && data->map[(int)y][(int)(x + 0.5)] == 'D')
			|| (direction < 0 && data->map[(int)y][(int)(x - 0.5)] == 'D'))
			return (1);
		if ((direction > 0 && data->map[(int)y][(int)(x + 0.5)] == 'd')
			|| (direction < 0 && data->map[(int)y][(int)(x - 0.5)] == 'd'))
			return (2);
	}
	return (0);
}

static bool	valid_door_position(t_data *data, int x, int y)
{
	if (x > 0 && x < data->map_width - 1 && y > 0 && y < data->map_height - 1)
	{
		if ((data->map[y][x - 1] == '1' && data->map[y][x + 1] == '1') &&
			(data->map[y - 1][x] == '0' && data->map[y + 1][x] == '0') &&
			(data->map[y - 1][x - 1] != '1' && data->map[y - 1][x + 1] != '1')
			&& (data->map[y + 1][x - 1] != '1'
			&& data->map[y + 1][x + 1] != '1'))
			return (true);
		if ((data->map[y - 1][x] == '1' && data->map[y + 1][x] == '1') &&
			(data->map[y][x - 1] == '0' && data->map[y][x + 1] == '0') &&
			(data->map[y - 1][x - 1] != '1' && data->map[y - 1][x + 1] != '1')
			&& (data->map[y + 1][x - 1] != '1'
			&& data->map[y + 1][x + 1] != '1'))
			return (true);
	}
	return (false);
}

void	place_doors(t_data *data)
{
	int	x;
	int	y;

	y = 1;
	while (y < data->map_height - 1)
	{
		x = 1;
		while (x < data->map_width - 1)
		{
			if (valid_door_position(data, x, y))
				data->map[y][x] = 'D';
			x++;
		}
		y++;
	}
}

void	door_interaction(t_data *data)
{
	int			door_y;
	int			door_x;
	static int	door_timer = 0;

	if (door_timer <= 0)
	{
		if (ft_is_near_door(data, 'y', 1) || ft_is_near_door(data, 'y', -1)
			|| ft_is_near_door(data, 'x', 1) || ft_is_near_door(data, 'x', -1))
		{
			door_y = (int)(data->player.pos_y + data->player.dir_y * 0.6);
			door_x = (int)(data->player.pos_x + data->player.dir_x * 0.6);
			if (data->map[door_y][door_x] == 'D')
				data->map[door_y][door_x] = 'd';
			else if (data->map[door_y][door_x] == 'd')
				data->map[door_y][door_x] = 'D';
			data->renderer.changed = true;
			door_timer = 1;
		}
	}
	else
	{
		door_timer--;
		data->renderer.changed = true;
	}
}
