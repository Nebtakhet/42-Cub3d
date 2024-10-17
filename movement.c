/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:54:53 by nvallin           #+#    #+#             */
/*   Updated: 2024/10/14 17:55:09 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	ft_rotate_player(t_data *data, char direction)
{
	if (direction == 'l')
	{
		data->player.angle -= 0.1;
		if (data->player.angle < 0)
			data->player.angle += 2 * PI;
		data->player.dir_x = cos(data->player.angle);
		data->player.dir_y = sin(data->player.angle);
	}
	if (direction == 'r')
	{
		data->player.angle += 0.1;
		if (data->player.angle > 2 * PI)
			data->player.angle -= 2 * PI;
		data->player.dir_x = cos(data->player.angle);
		data->player.dir_y = sin(data->player.angle);
	}
	data->player.moved = true;
}

void	ft_move_player_y(t_data *data, double dir_y, double *y_moved)
{
	if ((data->map[data->player_pos[0] + 1][data->player_pos[1]] != '1' || \
		(data->map[data->player_pos[0] + 1][data->player_pos[1]] == '1' \
		&& *y_moved < 3)) && dir_y > 0)
	{
		*y_moved += dir_y;
		//data->player.mini_player->instances[0].y += dir_y;
		if (*y_moved >= 8)
		{
			data->player_pos[0] += 1;
			data->player.mini_player->instances[0].y += 16;
			*y_moved = -8;
		}
	}
	else if ((data->map[data->player_pos[0] - 1][data->player_pos[1]] != '1' \
			|| (data->map[data->player_pos[0] - 1][data->player_pos[1]] == \
			'1' && *y_moved > -3)) && dir_y < 0)
	{
		//data->player.mini_player->instances[0].y += dir_y;
		*y_moved += dir_y;
		if (*y_moved <= -8)
		{
			data->player_pos[0] -= 1;
			data->player.mini_player->instances[0].y -= 16;
			*y_moved = 8;
		}		
	}	
}

void	ft_move_player_x(t_data *data, double dir_x, double *x_moved)
{
	if ((data->map[data->player_pos[0]][data->player_pos[1] + 1] != '1' || \
		(data->map[data->player_pos[0]][data->player_pos[1] + 1] == '1' \
		&& *x_moved < 3)) && dir_x > 0)
	{
		*x_moved += dir_x;
		//data->player.mini_player->instances[0].x += dir_x;
		if (*x_moved >= 8)
		{
			data->player_pos[1] += 1;
			data->player.mini_player->instances[0].x += 16;
			*x_moved = -8;
		}	
	}
	else if ((data->map[data->player_pos[0]][data->player_pos[1] -1] != '1' \
			|| (data->map[data->player_pos[0]][data->player_pos[1] - 1] == \
			'1' && *x_moved > -3)) && dir_x < 0)
	{
		//data->player.mini_player->instances[0].x += dir_x;
		*x_moved += dir_x;
		if (*x_moved <= -8)
		{
			data->player_pos[1] -= 1;
			data->player.mini_player->instances[0].x -= 16;
			*x_moved = 8;
		}		
	}
}

void	ft_move_player(t_data *data)
{
	static double	y = 0;
	static double	x = 0;

	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		ft_move_player_y(data, data->player.dir_y, &y);
		ft_move_player_x(data, data->player.dir_x, &x);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		ft_move_player_y(data, -data->player.dir_y, &y);
		ft_move_player_x(data, -data->player.dir_x, &x);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		ft_move_player_y(data, -data->player.dir_x, &y);
		ft_move_player_x(data, data->player.dir_y, &x);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		ft_move_player_y(data, data->player.dir_x, &y);
		ft_move_player_x(data, -data->player.dir_y, &x);
	}
	data->player.moved = true;
}
