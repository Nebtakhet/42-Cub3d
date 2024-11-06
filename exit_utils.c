/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:44:15 by cesasanc          #+#    #+#             */
/*   Updated: 2024/10/23 14:29:50 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	error_exit(t_data *data, char *str, int status)
{
	print_error(str);
	clean_exit(data, status);
}

void	print_error(char *str)
{
	if (str)
	{
		ft_putstr_fd("Cub3d Error: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	ft_free_data(t_data **info)
{
	if ((*info)->north_texture)
		mlx_delete_texture((*info)->north_texture);
	if ((*info)->south_texture)
		mlx_delete_texture((*info)->south_texture);
	if ((*info)->west_texture)
		mlx_delete_texture((*info)->west_texture);
	if ((*info)->east_texture)
		mlx_delete_texture((*info)->east_texture);
	if ((*info)->player.mini_p)
		mlx_delete_texture((*info)->player.mini_p);
	if ((*info)->door_texture)
		mlx_delete_texture((*info)->door_texture);
	if ((*info)->enemy)
		mlx_delete_texture((*info)->enemy);	
	if ((*info)->map)
		ft_free_array((*info)->map);
	if (*info)
	{
		free(*info);
		*info = NULL;
	}
}

void	clean_exit(t_data *data, int status)
{
	if (!data)
		exit(status);
	if (data->img)
		mlx_delete_image(data->mlx, data->img);
	if (data->mlx)
	{
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
	}
	ft_free_data(&data);
	exit(status);
}
