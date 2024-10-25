/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:24:13 by cesasanc          #+#    #+#             */
/*   Updated: 2024/10/23 13:08:20 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

// static int apply_lighting(int color, double lighting_factor)
// {
//     int r;
// 	int g;
// 	int b;
// 	int a;

//     r = (color >> 24) & 0xFF;
//     g = (color >> 16) & 0xFF;
//     b = (color >> 8) & 0xFF;
//     a = color & 0xFF;
//     r = (int)(r * lighting_factor);
//     g = (int)(g * lighting_factor);
//     b = (int)(b * lighting_factor);
//     if (r > 255)
// 		r = 255;
//     if (r < 0)
// 		r = 0;
//     if (g > 255)
// 		g = 255;
//     if (g < 0)
// 		g = 0;
//     if (b > 255)
// 		b = 255;
//     if (b < 0)
// 		b = 0;
//     return (get_rgba(r, g, b, a));
// }

/* Function to calculate the image to be rendered, placing the corresponding
pixel color in the image */
void	calculate_img(t_data *data)
{
	t_img		img;
	uint8_t		*clr;
	uint32_t	color;
	double		step;

	img.x = 0;
	while (img.x < WIDTH)
	{
		raycast(data, img.x);
		step = 1.0 * 64 / data->ray.line_height;
		data->ray.tex_pos = (data->ray.draw_start - HEIGHT / 2 + data->ray.line_height / 2) * step;
		img.y = data->ray.draw_start;
		while (img.y < data->ray.draw_end)
		{
			data->ray.tex_y = (int)data->ray.tex_pos & 63;
			data->ray.tex_pos += step;
			clr = ((uint8_t *)&((uint32_t *)data->east_texture->pixels)[64 * data->ray.tex_y + (64 - data->ray.tex_x - 1)]);
			color = get_rgba(clr[0], clr[1], clr[2], 255);
			if (data->ray.side == 1)
				color = (color >> 1) & 8355711;
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
		calculate_img(data);
		ft_draw_ray(data, data->palette[12]);
		frames = 0;
	}
	data->renderer.changed = false;
}
