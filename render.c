/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:24:13 by cesasanc          #+#    #+#             */
/*   Updated: 2024/10/22 13:02:49 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

/* Function to calculate the image to be rendered, placing the corresponding
pixel color in the image */
void	calculate_img(t_data *data)
{
	t_img	img;
	int		color;

	img.x = 0;
	while (img.x < WIDTH)
	{
		raycast(data);
		if (data->ray.side == 0)
			color = get_rgba(0, 255, 0, 255);
		else
			color = get_rgba(0, 0, 255, 255);
		img.y = 0;
		while (img.y < HEIGHT)
		{
			if (img.y >= data->ray.draw_start && img.y <= data->ray.draw_end)
				mlx_put_pixel(data->img, img.x, img.y, color);
			img.y++;
		}
		img.x++;
	}
}

/* Function to render the image. It will only render if the frames are greater
than the frame wait */
void	render(void *param)
{
	static int	frames = 0;
	t_data		*data;

	data = (t_data *)param;
	if (data->renderer.changed || ++frames > FRAME_WAIT)
	{
		draw_ceiling_and_floor(data);
		raycast(data);
		calculate_img(data);
		ft_draw_ray(data, data->palette[12]);
		frames = 0;
	}
	data->renderer.changed = false;
}
