/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:24:13 by cesasanc          #+#    #+#             */
/*   Updated: 2024/10/17 13:45:05 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

/* Function to calculate the image to be rendered, placing the corresponding
pixel color in the image */
void	calculate_img(t_data *data)
{
	t_img	img;

	img.x = 0;
	while (img.x < WIDTH)
	{
		img.y = 0;
		while (img.y < HEIGHT)
		{
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
		calculate_img(data);
	data->renderer.changed = false;
}
