/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:22:01 by nvallin           #+#    #+#             */
/*   Updated: 2024/10/08 14:34:48 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	main(int argc, char **argv)
{
	t_win	win;
	t_data	info;

	handle_args(argc, argv, &info);
	win_init(&win);
	mlx_loop_hook(win.mlx, &render, &win);
	mlx_image_to_window(win.mlx, win.img, 0, 0);
	mlx_loop(win.mlx);
	mlx_terminate(win.mlx);
	return (0);
}
