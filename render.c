/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:24:13 by cesasanc          #+#    #+#             */
/*   Updated: 2024/10/08 14:28:22 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	render(void *param)
{
	t_win	*win;

	win = (t_win *)param;
	if (win->renderer.frames < FRAME_WAIT)
	{
		win->renderer.frames++;
		return ;
	}
	win->renderer.frames = 0;
//	if (win->renderer.changed)
		//calculate_img(win);
	win->renderer.changed = false;
}
