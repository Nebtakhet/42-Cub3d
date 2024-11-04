/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:14:56 by cesasanc          #+#    #+#             */
/*   Updated: 2024/11/04 10:34:32 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	ft_get_door_texture(t_data *data)
{
	data->door_texture = mlx_load_png("textures/door2.png");
	if (!data->door_texture)
	{
		write(2, "Error\ninvalid door texture\n", 27);
		return (1);
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
			&& (data->map[y + 1][x - 1] != '1' && data->map[y + 1][x + 1] != '1'))
			return (true);
		if ((data->map[y - 1][x] == '1' && data->map[y + 1][x] == '1') &&
			(data->map[y][x - 1] == '0' && data->map[y][x + 1] == '0') &&
			(data->map[y - 1][x - 1] != '1' && data->map[y - 1][x + 1] != '1')
			&& (data->map[y + 1][x - 1] != '1' && data->map[y + 1][x + 1] != '1'))
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
			{
				data->map[y][x] = 'D';
				printf("Door placed at (%d, %d)\n", x, y);
			}
			x++;
		}
		y++;
	}
}
