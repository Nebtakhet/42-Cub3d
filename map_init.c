/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:02:22 by cesasanc          #+#    #+#             */
/*   Updated: 2024/10/23 12:49:18 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	ft_init_player(t_data *data)
{
	if (data->map[data->player_pos[0]][data->player_pos[1]] == 'N')
		data->player.angle = 3 * PI / 2;
	if (data->map[data->player_pos[0]][data->player_pos[1]] == 'S')
		data->player.angle = PI / 2;
	if (data->map[data->player_pos[0]][data->player_pos[1]] == 'W')
		data->player.angle = PI;
	if (data->map[data->player_pos[0]][data->player_pos[1]] == 'E')
		data->player.angle = 0;
	data->player.dir_x = cos(data->player.angle);
	data->player.dir_y = sin(data->player.angle);
	data->player.plane_x = -sin(data->player.angle) * 0.66;
	data->player.plane_y = cos(data->player.angle) * 0.66;
	data->player.pos_y = data->player_pos[0] + 0.5;
	data->player.pos_x = data->player_pos[1] + 0.5;
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

int	ft_get_map_str(int fd, char **map_str)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		*map_str = gnl_strjoin(*map_str, line);
		free(line);
		if (!*map_str)
		{
			perror("ft_parse_map");
			return (1);
		}
		line = get_next_line(fd);
	}
	if (!*map_str)
	{
		ft_parsing_error("missing map");
		return (1);
	}
	return (0);
}

t_data	*handle_args(int argc, char **argv, t_data *info)
{
	if (argc != 2)
	{
		write(2, "Please run cub3d with one scene description file\n", 49);
		return (NULL);
	}
	if (ft_strncmp((argv[1] + (ft_strlen(argv[1]) - 4)), ".cub", 5))
	{
		write(2, "Error\nScene description file of type .cub wanted\n", 49);
		return (NULL);
	}
	info = ft_init_data();
	if (!info)
		return (NULL);
	if (ft_parse_scene_description(info, argv[1]))
		return (NULL);
	ft_init_player(info);
	printf("floor RGB: %d,%d,%d\nceiling RGB: %d,%d,%d\nmap W: %d, H: %d\n", \
		info->floor_color[0], info->floor_color[1], info->floor_color[2], \
		info->ceiling_color[0], info->ceiling_color[1], info->ceiling_color[2], \
		info->map_width, info->map_height);
	int	i = 0;
	while (info->map[i] != NULL)
		printf("%s\n", info->map[i++]);
	//ft_free_data(&info);
	return (info);
}
