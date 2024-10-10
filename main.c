/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:22:01 by nvallin           #+#    #+#             */
/*   Updated: 2024/10/08 20:51:49 by cesasanc         ###   ########.fr       */
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
	mlx_loop_hook(data->mlx, &render, data);
	mlx_key_hook(data->mlx, &key_hook, data);
//	mlx_mouse_hook(data->mlx, &mouse_hook, data);
//	mlx_scroll_hook(data->mlx, &scroll_hook, data);
	mlx_close_hook(data->mlx, &close_program, data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	ft_draw_minimap(data);
	ft_draw_player_to_minimap(data);
	mlx_loop_hook(data->mlx, &ft_minimap_hook, (void *)data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}
