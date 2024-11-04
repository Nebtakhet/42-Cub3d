/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:26:48 by nvallin           #+#    #+#             */
/*   Updated: 2024/10/29 13:17:38 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	ft_draw_minimap_frame(t_data *data)
{
	int			x;
	int			y;
	mlx_image_t	*back;

	back = mlx_new_image(data->mlx, 320, 320);
	ft_memset(back->pixels, 124, 320 * 320 * sizeof(int32_t));
	mlx_image_to_window(data->mlx, back, 116, 116);
	data->map_frame = mlx_texture_to_image(data->mlx, data->north_texture);
	if (!data->map_frame || !mlx_resize_image(data->map_frame, 16, 16))
		return (1);
	y = 100;
	x = 100;
	while (y < 420)
	{
		if (mlx_image_to_window(data->mlx, data->map_frame, x, y) == -1)
			return (1);
		y += 16;
	}
	while (x < 420)
	{
		if (mlx_image_to_window(data->mlx, data->map_frame, x, y) == -1)
			return (1);
		x += 16;	
	}
	while (y > 100)
	{
		if (mlx_image_to_window(data->mlx, data->map_frame, x, y) == -1)
			return (1);
		y -= 16;
	}
	while (x > 100)
	{
		if (mlx_image_to_window(data->mlx, data->map_frame, x, y) == -1)
			return (1);
		x -= 16;	
	}
	return (0);
}

int	ft_draw_player_to_minimap(t_data *data)
{
	if (ft_draw_minimap_frame(data))
		return (1);
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
		250, 250) == -1)
		return (1);
	ft_draw_ray(data, data->palette[12]);
	ft_move_minimap_y(data, 0);
	ft_move_minimap_x(data, 0);
	return (0);
}

int	is_filled(char c, char filling)
{
	if (c == filling || ft_is_player(c))
		return (1);
	return (0);
}

int	draw_minimap(t_data *d, int x, int y)
{
	int	m_x;
	int	m_y;

	m_y = d->player_pos[0] + ((y - 250) / 16);
	m_x = d->player_pos[1] + ((x - 250) / 16);
//	int	i = 0;
//	while (d->map[i] != NULL)
//		printf("%s\n", d->map[i++]);
	if (!ft_is_player(d->map[m_y][m_x]) && (d->map[m_y][m_x] != '1'))
		d->map[m_y][m_x] = '0';
	else if (d->map[m_y][m_x] == '1')
	{
		d->minimap_walls++;
		if (mlx_image_to_window(d->mlx, d->map_wall, x ,y) == -1)
			return (1);
		return (0);
	}
	if (!is_filled(d->map[m_y + 1][m_x], '0') && draw_minimap(d, x, y + 16))
		return (1);
	if (!is_filled(d->map[m_y - 1][m_x], '0') && draw_minimap(d, x, y - 16))
		return (1);
	if (!is_filled(d->map[m_y][m_x + 1], '0') && draw_minimap(d, x + 16, y))
		return (1);
	if (!is_filled(d->map[m_y][m_x - 1], '0') && draw_minimap(d, x - 16, y))
		return (1);
	return (0);
}

void	ft_move_minimap_y(t_data *data, double direction)
{
	int	i;

	i = 0;
	while (i < data->minimap_walls)
	{
		if (direction > 0)
			data->map_wall->instances[i].y--;
		else
			data->map_wall->instances[i].y++;
		if (data->map_wall->instances[i].y > 100 && \
			data->map_wall->instances[i].y < 420 && \
			data->map_wall->instances[i].x > 100 && \
			data->map_wall->instances[i].x < 420)
			data->map_wall->instances[i].enabled = true;
		else
			data->map_wall->instances[i].enabled = false;
		i++;
	}
}

void	ft_move_minimap_x(t_data *data, double direction)
{
	int	i;

	i = 0;
	while (i < data->minimap_walls)
	{
		if (direction > 0)
			data->map_wall->instances[i].x--;
		else
			data->map_wall->instances[i].x++;
		if (data->map_wall->instances[i].y > 100 && \
			data->map_wall->instances[i].y < 420 && \
			data->map_wall->instances[i].x > 100 && \
			data->map_wall->instances[i].x < 420)
			data->map_wall->instances[i].enabled = true;
		else
			data->map_wall->instances[i].enabled = false;
		i++;
	}
}
