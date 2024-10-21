/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:24:13 by cesasanc          #+#    #+#             */
/*   Updated: 2024/10/21 09:53:24 by cesasanc         ###   ########.fr       */
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
		raycast(data, img.x);
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

	data = (t_data *)param;
	if (data->renderer.changed)
	{
		raycast(data, 0);
		calculate_img(data);
	}
	data->renderer.changed = false;
}
