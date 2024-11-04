/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:45:24 by cesasanc          #+#    #+#             */
/*   Updated: 2024/10/21 17:42:41 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	key_hook(mlx_key_data_t key_data, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key_data.key == MLX_KEY_ESCAPE)
	{
		clean_exit(data, 0);
		mlx_close_window(data->mlx);
	}
	data->renderer.changed = true;
}

/* Function to close the window and terminate the mlx instance */
void	close_program(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->mlx)
	{
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
	}
	exit(EXIT_SUCCESS);
}

void	ft_move_hook(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		ft_move_player(data, data->player.dir_y, data->player.dir_x);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		ft_move_player(data, -(data->player.dir_x), data->player.dir_y);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		ft_move_player(data, -(data->player.dir_y), -(data->player.dir_x));
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		ft_move_player(data, data->player.dir_x, -(data->player.dir_y));
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		ft_rotate_player(data, 'l');
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		ft_rotate_player(data, 'r');
	if (data->player.moved)
	{
		data->player.moved = false;
		data->renderer.changed = true;
	}
}
