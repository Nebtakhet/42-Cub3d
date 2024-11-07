/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:10:15 by cesasanc          #+#    #+#             */
/*   Updated: 2024/11/07 15:33:29 by cesasanc         ###   ########.fr       */
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
	if (y > 0 && y < data->map_height - 1 && x > 0 && \
		x < (int)ft_strlen(data->map[y]) - 1 && \
		!ft_is_player(data->map[y][x]))
	{
		if ((data->map[y][x - 1] == '0' && data->map[y][x + 1] == '0') &&
			(x < (int)ft_strlen(data->map[y - 1]) && data->map[y - 1][x] \
			== '0' && x < (int)ft_strlen(data->map[y + 1]) && \
			data->map[y + 1][x] == '0') && (x - 1 < \
			(int)ft_strlen(data->map[y - 1]) && data->map[y - 1][x - 1] == '0' \
			&& x + 1 < (int)ft_strlen(data->map[y - 1]) && \
			data->map[y - 1][x + 1] == '0') && (x - 1 < \
			(int)ft_strlen(data->map[y + 1]) && data->map[y + 1][x - 1] == '0' \
			&& x + 1 < (int)ft_strlen(data->map[y + 1]) && \
			data->map[y + 1][x + 1] == '0') && (x - 2 > 0 && x - 2 < \
			(int)ft_strlen(data->map[y - 2]) && data->map[y - 2][x - 2] == '0' \
			&& x + 2 < (int)ft_strlen(data->map[y - 2]) && \
			data->map[y - 2][x + 2] == '0'))
			return (true);
	}
	return (false);
}
/*
static int	ft_is_near_enemy(t_data *data, char axis, int direction)
{
	double	y;
	double	x;

	y = data->player.pos_y;
	x = data->player.pos_x;
	if (axis == 'y')
	{
		if ((direction > 0 && data->map[(int)(y + 2.5)][(int)x] == 'X')
			|| (direction < 0 && data->map[(int)(y - 2.5)][(int)x] == 'X'))
			return (1);
	}
	if (axis == 'x')
	{
		if ((direction > 0 && data->map[(int)y][(int)(x + 2.5)] == 'X')
			|| (direction < 0 && data->map[(int)y][(int)(x - 2.5)] == 'X'))
			return (1);
	}
	return (0);
}*/

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
	double	enemy_x;
	double	enemy_y;

	enemy_y = (int)data->player.pos_y;
	enemy_x = (int)data->player.pos_x;
	while (enemy_y - data->player.pos_y < 4 && \
		enemy_y - data->player.pos_y > -4 && \
		enemy_x - data->player.pos_x < 4 && \
		enemy_x - data->player.pos_x > -4 && \
		enemy_y > 0 && enemy_y < data->map_height - 1 && \
		enemy_x > 0 && enemy_x < (int)ft_strlen(data->map[(int)enemy_y]) - 1 && \
		data->map[(int)enemy_y][(int)enemy_x] != 'X' && \
		data->map[(int)enemy_y][(int)enemy_x] != '1' && \
		data->map[(int)enemy_y][(int)enemy_x] != 'D')
	{
		enemy_y += data->player.dir_y / 20;
		enemy_x += data->player.dir_x / 20;
	}
	if (data->map[(int)enemy_y][(int)enemy_x] == 'X')
	{
		data->map[(int)enemy_y][(int)enemy_x] = '0';
		data->enemy_count--;
		data->renderer.changed = true;
	}
}

/*
void	enemies_interaction(t_data *data)
{
	int	enemy_x;
	int	enemy_y;

	if ((ft_is_near_enemy(data, 'y', 1) || ft_is_near_enemy(data, 'y', -1))
		|| ft_is_near_enemy(data, 'x', 1) || ft_is_near_enemy(data, 'x', -1))
	{
		enemy_y = (int)(data->player.pos_y + data->player.dir_y * 1.5);
		enemy_x = (int)(data->player.pos_x + data->player.dir_x * 1.5);
		if (data->map[enemy_y][enemy_x] == 'X')
		{
			data->map[enemy_y][enemy_x] = '0';
			data->enemy_count--;
			data->renderer.changed = true;
		}
	}
}*/

void	kill_count(t_data *data)
{
	char		*count;
	char		*itoa;

	itoa = ft_itoa(data->enemy_count);
	if (!itoa)
		return ;
	count = ft_strjoin(itoa, " enemies left");
	if (!count)
	{
		free(itoa);
		return ;
	}
	if (data->enemy_string)
		mlx_delete_image(data->mlx, data->enemy_string);
	data->enemy_string = mlx_put_string(data->mlx, count, WIDTH / 2, 30);
	mlx_resize_image(data->enemy_string, data->enemy_string->width
		+ 500, data->enemy_string->height + 50);
	data->renderer.changed = true;
	you_win(data);
	free(itoa);
	free(count);
}
