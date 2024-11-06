/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:17:01 by cesasanc          #+#    #+#             */
/*   Updated: 2024/11/06 19:17:11 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	raycast(t_data *data, int x)
{
	init_ray(data, x);
	set_dda(data);
	perform_dda(data);
	calc_wall(data);
}
