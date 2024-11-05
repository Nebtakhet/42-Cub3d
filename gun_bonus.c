/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:51:02 by cesasanc          #+#    #+#             */
/*   Updated: 2024/11/05 16:45:10 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	load_frames(t_data *data)
{
	int				i;
	char			*filename;
	mlx_texture_t	*gun;

	if (data->gun[0] != NULL)
		return ;
	filename = ft_strdup("textures/gun/frame_0.png");
	if (!filename)
		print_error("Error allocating memory for gun filename");
	i = -1;
	while (i++ < 4)
	{
		filename[19] = i + '0';
		gun = mlx_load_png(filename);
		if (!gun)
			print_error("Error loading gun PNG");
		data->gun[i] = mlx_texture_to_image(data->mlx, gun);
		if (!data->gun[i])
			print_error("Error converting gun texture to image");
		mlx_resize_image(data->gun[i], gun->width * 6, gun->height * 6);
		mlx_delete_texture(gun);
	}
	free(filename);
}

static void	start_shooting(t_data *data, int *frame, bool *shooting)
{
	*shooting = true;
	*frame = 1;
	enemies_interaction(data);
}

static void	update_frame(t_data *data, int *frame)
{
	int	x_offset;

	x_offset = 0;
	if (*frame == 1)
		x_offset = -60;
	if (*frame >= 1)
		data->gun[*frame - 1]->enabled = false;
	if (mlx_image_to_window(data->mlx, data->gun[*frame],
			WIDTH / 2 - data->gun[*frame]->width / 2 + x_offset,
			HEIGHT - data->gun[*frame]->height) == -1)
		print_error("Error drawing gun frame");
	data->gun[*frame]->enabled = true;
	(*frame)++;
}

void	ft_shoot(void *param)
{
	static int	frame = 0;
	static bool	shooting = false;
	t_data		*data;

	data = (t_data *)param;
	if (!data->gun[0])
		load_frames(data);
	if ((mlx_is_key_down(data->mlx, MLX_KEY_SPACE) || \
		mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT)) && !shooting)
		start_shooting(data, &frame, &shooting);
	if (shooting)
		update_frame(data, &frame);
	else if (frame == 0)
	{
		mlx_image_to_window(data->mlx, data->gun[0],
			WIDTH / 2 - data->gun[0]->width / 2,
			HEIGHT - data->gun[0]->height);
		data->gun[0]->enabled = true;
	}
	if (frame > 4)
	{
		shooting = false;
		frame = 0;
	}
	data->renderer.changed = true;
}
