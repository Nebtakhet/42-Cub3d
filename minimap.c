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

void	ft_minimap_hook(void *param)
{
	t_data		*data = param;
	static int	x = 0;
	static int	y = 0;

	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		if (data->map[data->player_pos[0] - 1][data->player_pos[1]] != '1' \
			|| (data->map[data->player_pos[0] - 1][data->player_pos[1]] == '1' \
			&& y > -3))
		{
			data->player.mini_player->instances[0].y -= 1;
			y--;
			if (y == -8 && data->map[data->player_pos[0] - 1][data->player_pos[1]] != '1')
			{
				data->player_pos[0] -= 1;
				y = 8;
			}
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		if (data->map[data->player_pos[0] + 1][data->player_pos[1]] != '1' || \
			(data->map[data->player_pos[0] + 1][data->player_pos[1]] == '1' && \
			y < 3))
		{
			data->player.mini_player->instances[0].y += 1;
			y++;
			if (y == 8 && data->map[data->player_pos[0] + 1][data->player_pos[1]] != '1')
			{
				data->player_pos[0] += 1;
				y = -8;
			}
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		if (data->map[data->player_pos[0]][data->player_pos[1] - 1] != '1' || \
			(data->map[data->player_pos[0]][data->player_pos[1] - 1] == '1' \
			&& x > -3))
		{
			data->player.mini_player->instances[0].x -= 1;
			x--;
			if (x == -8 && data->map[data->player_pos[0]][data->player_pos[1] - 1] != '1')
			{
				data->player_pos[1] -= 1;
				x = 8;
			}
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		if (data->map[data->player_pos[0]][data->player_pos[1] + 1] != '1' || \
			(data->map[data->player_pos[0]][data->player_pos[1] + 1] == '1' \
			&& x < 3))
		{
			data->player.mini_player->instances[0].x += 1;
			x++;
			if (x == 8 && data->map[data->player_pos[0]][data->player_pos[1] + 1] != '1')
			{
				data->player_pos[1] += 1;
				x = -8;
			}
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player.angle -= 0.1;
		if (data->player.angle < 0)
			data->player.angle += 2 * PI;
		data->player.dir_x = cos(data->player.angle) * 5;
		data->player.dir_y = sin(data->player.angle) * 5;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player.angle += 0.1;
		if (data->player.angle > 2 * PI)
			data->player.angle -= 2 * PI;
		data->player.dir_x = cos(data->player.angle) * 5;
		data->player.dir_y = sin(data->player.angle) * 5;
	}
}

int	ft_draw_player_to_minimap(t_data *data)
{
	data->player.mini_p = mlx_load_png("./textures/mossy.png");
	if (!data->player.mini_p)
		return (1);
	data->player.mini_player = mlx_texture_to_image(data->mlx, data->player.mini_p);
	if (!data->player.mini_player)
		return (1);
	if (!mlx_resize_image(data->player.mini_player, 16, 16))
		return (1);
	if (mlx_image_to_window(data->mlx, data->player.mini_player, \
		data->player_pos[1] * 16 + 20, data->player_pos[0] * 16 + 20) == -1)
		return (1);
	return (0);
}

void	ft_draw_minimap(t_data *data)
{
    mlx_image_t* img;
	int	y;
	int	x;
	int	i;
	int	i2;

	y = -1;
    img = mlx_new_image(data->mlx, data->map_width * 16, data->map_height * 16);
  ft_memset(img->pixels, 200, img->width * img->height * sizeof(int32_t));
    mlx_image_to_window(data->mlx, img, 20, 20);
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
		{
			if (data->map[y][x] == '1')
			{
				i2 = y * 16;
				while (i2++ - y * 16 < 16)
				{
					i = x * 16;
					while (i - x * 16 < 16)
						mlx_put_pixel(img, i++, i2, 0x808080);
				}
			}
		}
	}
}
