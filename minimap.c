/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:26:48 by nvallin           #+#    #+#             */
/*   Updated: 2024/10/10 14:33:17 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	ft_draw_player_to_minimap(t_data *data)
{
	data->player.mini_p = mlx_load_png("./textures/player1.png");
	if (!data->player.mini_p)
		return (1);
	data->player.mini_player = \
	mlx_texture_to_image(data->mlx, data->player.mini_p);
	if (!data->player.mini_player)
		return (1);
	if (!mlx_resize_image(data->player.mini_player, 16, 16))
		return (1);
	if (mlx_image_to_window(data->mlx, data->player.mini_player, \
		data->player_pos[1] * 16 + 20, data->player_pos[0] * 16 + 20) == -1)
		return (1);
	return (0);
}

int	ft_draw_minimap(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	data->map_wall = mlx_texture_to_image(data->mlx, data->east_texture);
	data->map_floor = mlx_texture_to_image(data->mlx, data->north_texture);
	if (!data->map_wall || !data->map_floor || \
		!mlx_resize_image(data->map_wall, 16, 16) || \
		!mlx_resize_image(data->map_floor, 16, 16))
		return (1);
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width && data->map[y][x])
		{
			if (data->map[y][x] == '1' && mlx_image_to_window(data->mlx, \
				data->map_wall, x * 16 + 20, y * 16 + 20) == -1)
				return (1);
			if ((data->map[y][x] == '.' || ft_is_player(data->map[y][x])) && \
				mlx_image_to_window(data->mlx, data->map_floor, x * 16 + 20, \
									y * 16 + 20) == -1)
				return (1);
		}
	}
	return (0);
}
