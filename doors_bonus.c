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
	if (x > 0 && x < (int)ft_strlen(data->map[y]) - 1 && \
		y > 0 && y < data->map_height - 1)
	{
		if ((data->map[y][x - 1] == '1' && data->map[y][x + 1] == '1') &&
			((data->map[y - 1][x] == '0' || data->map[y - 1][x] == '.') && \
			(data->map[y + 1][x] == '0' || data->map[y + 1][x] == '.')) &&
			(data->map[y - 1][x - 1] != '1' && data->map[y - 1][x + 1] != '1')
			&& (data->map[y + 1][x - 1] != '1'
			&& data->map[y + 1][x + 1] != '1'))
			return (true);
		if ((data->map[y - 1][x] == '1' && data->map[y + 1][x] == '1') &&
			((data->map[y][x - 1] == '0' || data->map[y][x - 1] == '.') && \
			(data->map[y][x + 1] == '0' || data->map[y][x + 1] == '.')) &&
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
	while (y < data->map_height - 3)
	{
		x = 1;
		while (x < (int)ft_strlen(data->map[y]) - 3)
		{
			if (valid_door_position(data, x, y))
				data->map[y][x] = 'd';
			x++;
		}
		y++;
	}
}

int	find_door_instance(t_data *data)
{
	int	i;

	i = 82;
	while (i - 82 < data->minimap_doors)
	{
		if ((data->player.mini_player->instances[0].y + 8) + data->player.dir_y * 0.3 >= data->map_frame->instances[i].y
			&& (data->player.mini_player->instances[0].y + 8) + data->player.dir_y * 0.3 <= data->map_frame->instances[i].y + 16
			&& (data->player.mini_player->instances[0].x + 8) + data->player.dir_x * 0.3 >= data->map_frame->instances[i].x
			&& (data->player.mini_player->instances[0].x + 8) + data->player.dir_x * 0.3 <= data->map_frame->instances[i].x + 16)
			break ;
		i++;
	}
	return (i);
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
			{
				data->map[door_y][door_x] = 'd';
				data->map_frame->instances[find_door_instance(data)].enabled = false;
				mlx_set_instance_depth(&data->map_frame->instances[find_door_instance(data)], 100);
				printf("Door opened at (%d, %d)\n", door_x, door_y);
			}
			else if (data->map[door_y][door_x] == 'd' && data->map\
					[(int)data->player.pos_y][(int)data->player.pos_x] != 'd')
			{
				data->map[door_y][door_x] = 'D';
				data->map_frame->instances[find_door_instance(data)].enabled = true;
				mlx_set_instance_depth(&data->map_frame->instances[find_door_instance(data)], 10);
				printf("Door closed at (%d, %d)\n", door_x, door_y);
			}
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
