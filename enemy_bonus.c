/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:10:15 by cesasanc          #+#    #+#             */
/*   Updated: 2024/11/06 14:49:38 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	get_enemy_texture(t_data *data)
{
	data->enemy = mlx_load_png("textures/enemy2.png");
	if (!data->enemy)
	{
		write(2, "Error\ninvalid enemy texture\n", 28);
		return (1);
	}
	return (0);
}

static bool	valid_enemy_position(t_data *data, int x, int y)
{
	if (x > 0 && x < data->map_width - 1 && y > 0 && y < data->map_height - 1)
	{
		if ((data->map[y][x - 1] == '0' && data->map[y][x + 1] == '0') &&
			(data->map[y - 1][x] == '0' && data->map[y + 1][x] == '0') &&
			(data->map[y - 1][x - 1] == '0' && data->map[y - 1][x + 1] == '0')
			&& (data->map[y + 1][x - 1] == '0'
			&& data->map[y + 1][x + 1] == '0')
			&& (data->map[y - 2][x - 2] == '0'
			&& data->map[y - 2][x + 2] == '0'))
			return (true);
	}
	return (false);
}

void	place_enemies(t_data *data)
{
	int	x;
	int	y;
	int	count;

	y = 1;
	count = 0;
	while (y < data->map_height - 1)
	{
		x = 1;
		while (x < data->map_width - 1)
		{
			if (valid_enemy_position(data, x, y))
			{
				data->map[y][x] = 'X';
				count++;
			}
			x++;
		}
		y++;
	}
	data->enemy_count = count;
}

void	enemies_interaction(t_data *data)
{
	int	enemy_x;
	int	enemy_y;

	enemy_y = (int)(data->player.pos_y + data->player.dir_y * 2.5);
	enemy_x = (int)(data->player.pos_x + data->player.dir_x * 2.5);

	if (enemy_y > 0 && enemy_y < data->map_height && 
		enemy_x > 0 && enemy_x < data->map_width &&
		data->map[enemy_y][enemy_x] == 'X')
	{
		data->map[enemy_y][enemy_x] = '0';
		data->enemy_count--;
		data->renderer.changed = true;
	}
}

void	kill_count(t_data *data)
{
	char	*count;

	count = ft_strjoin(ft_itoa(data->enemy_count), " enemies left");
	mlx_put_string(data->mlx, count, WIDTH / 2, 10);
	data->renderer.changed = true;
	free(count);
}
