/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:24:13 by cesasanc          #+#    #+#             */
/*   Updated: 2024/10/08 15:08:18 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	calculate_img(t_data *data)
{
	t_img	img;

	img.x = 0;
	while (img.x < WIDTH)
	{
		img.y = 0;
		while (img.y < HEIGHT)
		{
			mlx_put_pixel(data->img, img.x, img.y, data->palette[12]);
			img.y++;
		}
		img.x++;		
	}	
}

void	render(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->renderer.frames < FRAME_WAIT)
	{
		data->renderer.frames++;
		return ;
	}
	data->renderer.frames = 0;
	if (data->renderer.changed)
		calculate_img(data);
	data->renderer.changed = false;
}
