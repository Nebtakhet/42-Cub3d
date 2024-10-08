/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:22:01 by nvallin           #+#    #+#             */
/*   Updated: 2024/10/07 15:22:04 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

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
	if ((*info)->map)
		ft_free_array((*info)->map);
	if (*info)
	{
		free(*info);
		*info = NULL;
	}
}

t_data	*ft_init_data(void)
{
	t_data	*info;

	info = malloc(sizeof(t_data));
	if (!info)
	{
		perror("Error\nft_init_data");
		return (NULL);
	}
	info->floor_color[0] = -1;
	info->ceiling_color[0] = -1;
	info->north_texture = NULL;
	info->south_texture = NULL;
	info->west_texture = NULL;
	info->east_texture = NULL;
	info->map = NULL;
	info->map_width = 0;
	info->map_height = 0;
	return (info);
}

int	main(int argc, char **argv)
{
	t_data	*info;

	if (argc != 2)
	{
		write(2, "Please run cub3d with one scene description file\n", 49);
		return (1);
	}
	if (ft_strncmp((argv[1] + (ft_strlen(argv[1]) - 4)), ".cub", 5))
	{
		write(2, "Error\nScene description file of type .cub wanted\n", 49);
		return (1);
	}
	info = ft_init_data();
	if (!info)
		return (1);
	if (ft_parse_scene_description(info, argv[1]))
		return (1);
	printf("floor RGB: %d,%d,%d\nceiling RGB: %d,%d,%d\nmap W: %d, H: %d\n",\
		info->floor_color[0], info->floor_color[1], info->floor_color[2], \
		info->ceiling_color[0], info->ceiling_color[1], info->ceiling_color[2], \
		info->map_width, info->map_height);
	int	i = 0;
	while (info->map[i] != NULL)
		printf("%s\n", info->map[i++]);
	ft_free_data(&info);
	return (0);
}
