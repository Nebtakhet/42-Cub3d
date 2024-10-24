/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:59:55 by nvallin           #+#    #+#             */
/*   Updated: 2024/10/23 12:51:31 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	ft_get_map(t_data *info, char *map_str)
{
	int	i;
	int	len;

	i = -1;
	info->map = malloc((info->map_height + 1) * sizeof(char *));
	while (info->map && ++i < info->map_height)
	{
		len = gnl_strchr_index(map_str, '\n');
		info->map[i] = gnl_strldup(map_str, len);
		if (!info->map[i])
			break ;
		map_str += (len + 1);
	}
	if (i == info->map_height)
	{
		info->map[i] = NULL;
		ft_find_player(info);
		return (0);
	}
	perror("ft_get_map");
	return (1);
}

int	ft_check_map_end(char *map_str, int player_count)
{
	if (player_count == 0)
	{
		ft_parsing_error("no player found");
		return (1);
	}
	while (*map_str == '\n')
		map_str++;
	if (*map_str == '\0')
		return (0);
	if (*map_str != '0' && *map_str != '1' && *map_str != 'N' && \
		*map_str != 'S' && *map_str != 'E' && *map_str != 'W' && \
		*map_str != ' ')
		ft_parsing_error("map has to be the last element in file");
	else
		ft_parsing_error("map can't be seperated by newline");
	return (1);
}

int	ft_check_player(t_data *info, int *player_count, int x)
{
	*player_count += 1;
	if (*player_count == 1)
	{
		info->player_pos[0] = info->map_height;
		info->player_pos[1] = x;
		return (0);
	}
	if (*player_count > 1)
		ft_parsing_error("multiple players found");
	return (1);
}

int	ft_check_map_content(t_data *info, char *map)
{
	int	player;
	int	width;

	width = 0;
	player = 0;
	while (*map)
	{
		if (width > info->map_width)
			info->map_width = width;
		if (!ft_is_valid_content(*map))
			return (1);
		if (*map == '\n')
		{
			width = -1;
			info->map_height++;
			if (*(map + 1) == '\n')
				break ;
		}
		if (ft_is_player(*map++) && ft_check_player(info, &player, width))
			return (1);
		width++;
	}
	if (ft_check_map_end(map, player))
		return (1);
	return (0);
}

int	ft_parse_map(t_data *info, int fd, char **line)
{
	char	*map_str;

	map_str = ft_strdup(*line);
	free(*line);
	*line = NULL;
	if (!map_str)
	{
		perror("ft_parse_map");
		return (1);
	}
	if (ft_get_map_str(fd, &map_str) || ft_check_map_content(info, map_str) \
		|| ft_get_map(info, map_str) || \
		ft_flood_fill(info, info->player_pos[1], info->player_pos[0]))
	{
		if (map_str)
			free(map_str);
		return (1);
	}
	free(map_str);
	return (0);
}
