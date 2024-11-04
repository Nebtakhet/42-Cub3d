/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:22:01 by nvallin           #+#    #+#             */
/*   Updated: 2024/11/04 11:17:47 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	data = handle_args(argc, argv, data);
	if (!data)
		return (1);
	win_init(data);
	mlx_key_hook(data->mlx, &key_hook, data);
	mlx_close_hook(data->mlx, &close_program, data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_loop_hook(data->mlx, &render, data);
	mlx_loop_hook(data->mlx, &ft_move_hook, (void *)data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}
