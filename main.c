/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:22:01 by nvallin           #+#    #+#             */
/*   Updated: 2024/11/04 10:33:28 by cesasanc         ###   ########.fr       */
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
	mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_cursor_hook(data->mlx, &cursor_hook, data);
	mlx_close_hook(data->mlx, &close_program, data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	ft_get_door_texture(data);
	data->map_wall = mlx_texture_to_image(data->mlx, data->east_texture);
	data->door_wall = mlx_texture_to_image(data->mlx, data->door_texture);
	if (!data->map_wall || !mlx_resize_image(data->map_wall, 16, 16))
		return (1);
	if (draw_minimap(data, 250, 250) || ft_draw_player_to_minimap(data))
		return (1);
//	place_doors(data);
	int	i = 0;
	while (data->map[i] != NULL)
		printf("%s\n", data->map[i++]);
	mlx_loop_hook(data->mlx, &render, data);
	mlx_loop_hook(data->mlx, &ft_move_hook, (void *)data);
	mlx_loop_hook(data->mlx, &ft_shoot, (void *)data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}
