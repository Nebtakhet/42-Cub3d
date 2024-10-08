/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:20:44 by nvallin           #+#    #+#             */
/*   Updated: 2024/10/07 15:20:45 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	ft_get_north_texture(t_data *info, char *line)
{
	int	i;

	line[ft_strlen(line) - 1] = '\0';
	i = 0;
	while (line[i] == ' ')
		i++;
	info->north_texture = mlx_load_png(&line[i]);
	if (!info->north_texture)
	{
		write(2, "Error\ninvalid north texture\n", 28);
		return (1);
	}
	return (0);
}

int	ft_get_south_texture(t_data *info, char *line)
{
	int	i;

	line[ft_strlen(line) - 1] = '\0';
	i = 0;
	while (line[i] == ' ')
		i++;
	info->south_texture = mlx_load_png(&line[i]);
	if (!info->south_texture)
	{
		write(2, "Error\ninvalid south texture\n", 28);
		return (1);
	}
	return (0);
}

int	ft_get_west_texture(t_data *info, char *line)
{
	int	i;

	line[ft_strlen(line) - 1] = '\0';
	i = 0;
	while (line[i] == ' ')
		i++;
	info->west_texture = mlx_load_png(&line[i]);
	if (!info->west_texture)
	{
		write(2, "Error\ninvalid west texture\n", 27);
		return (1);
	}
	return (0);
}

int	ft_get_east_texture(t_data *info, char *line)
{
	int	i;

	line[ft_strlen(line) - 1] = '\0';
	i = 0;
	while (line[i] == ' ')
		i++;
	info->east_texture = mlx_load_png(&line[i]);
	if (!info->east_texture)
	{
		write(2, "Error\ninvalid east texture\n", 27);
		return (1);
	}
	return (0);
}
