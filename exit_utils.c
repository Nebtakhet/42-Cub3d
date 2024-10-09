/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:44:15 by cesasanc          #+#    #+#             */
/*   Updated: 2024/10/09 12:06:06 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	print_error(char *str)
{
	if (str)
	{
		ft_putstr_fd("Cub3d Error: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	clean_exit(t_data *data, int status)
{
	if (!data)
		exit(status);
	if (data->img)
	{
		mlx_delete_image(data->mlx, data->img);
		free(data->img);
	}
	if (data->mlx)
	{
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
		free(data->mlx);
	}
	free(data);
	exit(status);
}
