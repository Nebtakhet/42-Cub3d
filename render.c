/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:24:13 by cesasanc          #+#    #+#             */
/*   Updated: 2024/10/21 17:40:19 by cesasanc         ###   ########.fr       */
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
			color = 0x00FF00;
		else
			color = 0x0000FF;
		img.y = 0;
		while (img.y < HEIGHT)
		{
			if (img.y >= data->ray.draw_start && img.y <= data->ray.draw_end)
				mlx_put_pixel(data->img, img.x, img.y, color);
			else
				mlx_put_pixel(data->img, img.x, img.y, 0x000000);
			img.y++;
		}
		img.x++;
	}
}

/* Function to render the image. It will only render if the frames are greater
than the frame wait */
void	render(void *param)
{
	t_data	*data;
	int		frames;

	data = (t_data *)param;
	frames = 0;
	ft_draw_ray(data, data->palette[12]);
	if (data->renderer.changed || frames > FRAME_WAIT)
	{
		ft_draw_ray(data, data->palette[12]);
		raycast(data);
		calculate_img(data);
	}
	data->renderer.changed = false;
}
