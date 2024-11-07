/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:17:08 by cesasanc          #+#    #+#             */
/*   Updated: 2024/11/07 15:33:52 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	you_win(t_data *data)
{
	if (!data->enemy_count && !data->you_win)
	{
		data->you_win = mlx_put_string(data->mlx, "YOU WIN!", WIDTH / 2.5, \
		HEIGHT / 2.5);
		mlx_resize_image(data->you_win, 500, 200);
	}
}
